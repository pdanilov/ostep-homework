In this homework, you’ll measure the costs of a system call and context
switch. Measuring the cost of a system call is relatively easy. For example,
you could repeatedly call a simple system call (e.g., performing a 0-byte
read), and time how long it takes; dividing the time by the number of
iterations gives you an estimate of the cost of a system call.
One thing you’ll have to take into account is the precision and accuracy of your timer. A typical timer that you can use is gettimeofday();
read the man page for details. What you’ll see there is that gettimeofday()
returns the time in microseconds since 1970; however, this does not mean
that the timer is precise to the microsecond. Measure back-to-back calls
to gettimeofday() to learn something about how precise the timer really is; this will tell you how many iterations of your null system-call
test you’ll have to run in order to get a good measurement result. If
gettimeofday() is not precise enough for you, you might look into
using the rdtsc instruction available on x86 machines.
Measuring the cost of a context switch is a little trickier. The lmbench
benchmark does so by running two processes on a single CPU, and setting up two UNIX pipes between them; a pipe is just one of many ways
processes in a UNIX system can communicate with one another. The first
process then issues a write to the first pipe, and waits for a read on the
second; upon seeing the first process waiting for something to read from
the second pipe, the OS puts the first process in the blocked state, and
switches to the other process, which reads from the first pipe and then
writes to the second. When the second process tries to read from the first
pipe again, it blocks, and thus the back-and-forth cycle of communication
continues. By measuring the cost of communicating like this repeatedly,
lmbench can make a good estimate of the cost of a context switch. You
can try to re-create something similar here, using pipes, or perhaps some
other communication mechanism such as UNIX sockets.
One difficulty in measuring context-switch cost arises in systems with
more than one CPU; what you need to do on such a system is ensure that
your context-switching processes are located on the same processor. Fortunately, most operating systems have calls to bind a process to a particular processor; on Linux, for example, the sched setaffinity() call
is what you’re looking for. By ensuring both processes are on the same
processor, you are making sure to measure the cost of the OS stopping
one process and restoring another on the same CPU.

1. For measuring syscall duration we'll repeat empty `read()` many times using command line parameter to vary number of repeats. Then, we can select appropriate number of iterations with subsequent executions with the same parameter value: if resulting duration varies significantly from launch to launch, then we need to increase our parameter.

    ```c
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
    ```

    After repeating the process of finding parameter's optimal value seems to be 10<sup>6</sup>.

    ```sh
    prompt> gcc ./code/syscall.c -o ./bin/syscall
    prompt> ./bin/syscall 1000000
    Average time per system call: 0.602 microseconds
    ```
2. To measure context switch time we'll create two pipes that will be used by two processes to write/read and read/write respectively. Using the same idea from the previous task, we'll repeat the process many times varying by console argument.

    ```c
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
    ```

    For this task optimal value of iterations is 10<sup>5</sup>.

    ```sh
    prompt> gcc ./code/contextswitch.c -o ./bin/contextswitch
    prompt> ./bin/contextswitch 100000
    Average time per context switch: 3.450745 microseconds
    ```
