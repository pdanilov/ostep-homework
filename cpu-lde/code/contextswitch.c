#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sched.h>

int main(int argc, char *argv[]) {
    assert(argc == 2);
    int iterations = atoi(argv[1]);

    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);

    if (fork() == 0) {
        sched_setaffinity(0, sizeof(cpu_set_t), &mask);
        char buf;
        for (int i = 0; i < iterations; i++) {
            write(pipe1[1], "a", 1);
            read(pipe2[0], &buf, 1);
        }
    } else {
        sched_setaffinity(0, sizeof(cpu_set_t), &mask);
        struct timeval start, end;
        char buf;

        gettimeofday(&start, NULL);
        for (int i = 0; i < iterations; i++) {
            read(pipe1[0], &buf, 1);
            write(pipe2[1], "b", 1);
        }
        gettimeofday(&end, NULL);

        long time_taken = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
        printf("Average time per context switch: %f microseconds\n", (double)time_taken / (2 * iterations));
    }

    return 0;
}
