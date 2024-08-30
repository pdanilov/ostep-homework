#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    assert(argc == 2);
    int iterations = atoi(argv[1]);
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < iterations; i++) {
        read(0, NULL, 0);
    }

    gettimeofday(&end, NULL);
    long time_taken = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
    printf("Average time per system call: %.3f microseconds\n", (double)time_taken / iterations);
}
