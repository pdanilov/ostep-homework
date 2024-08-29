1.  - Q: Write a program that calls fork(). Before calling fork(), have the
main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process?
What happens to the variable when both the child and parent change
the value of x?

    - A: Initial value of variable `x` in the child process is the same as in the main process since `fork()` creates copy of initial program. When variable `x` is changed in some of two processes it only changes locally since `fork()` creates another process with separate address space.

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <unistd.h>

        int main() {
            int x = 100;
            int rc = fork();
            if (rc < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
            } else {
                char *loc = (rc == 0) ? "child" : "parent";
                printf("%s before incr: x = %d\n", loc, x);
                x++;
                printf("%s before incr: x = %d\n", loc, x);
            }
        }
        ```

        ```sh
        prompt> gcc code/q1.c -o bin/q1
        prompt> ./bin/q1
        parent before incr: x = 100
        parent before incr: x = 101
        child before incr: x = 100
        child before incr: x = 101
        ```

2.  - Q: Write a program that opens a file (with the open() system call)
and then calls fork() to create a new process. Can both the child
and parent access the file descriptor returned by open()? What
happens when they are writing to the file concurrently, i.e., at the
same time?

    - A: It's possible to use the same file descriptor from the child process since copy created with `fork()` has the same file descriptors that were open in the parent process. Concurrent writing from two processes leads to undefined order of these writes.

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <unistd.h>

        int main(int argc, char *argv[]) {
            FILE *file = fopen(argv[1], "w");
            int rc = fork();
            if (rc < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
            } else {
                char *loc = (rc == 0) ? "child" : "parent";
                fprintf(file, "appending to the file from %s\n", loc);
            }
            fclose(file);
        }
        ```

        ```sh
        prompt> gcc code/q2.c -o bin/q2
        prompt> ./bin/q2 /tmp/q2.txt
        prompt> cat /tmp/q2.txt
        appending to the file from parent
        appending to the file from child
        ```

3.  - Q: Write another program using fork(). The child process should
print “hello”; the parent process should print “goodbye”. You should
try to ensure that the child process always prints first; can you do
this without calling wait() in the parent?

    - A: There is no way to synchronize an order of execution parent/child programs since their address spaces are different, and the only way is to use system calls `wait()` or `waitpid()`.

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <unistd.h>

        int main() {
            int rc = fork();
            int status;
            if (rc < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
            } else if (rc == 0) {
                printf("hello\n");
            } else {
                waitpid(rc, NULL, 0);
                printf("goodbye\n");
            }
        }
        ```

4.  - Q: Write a program that calls fork() and then calls some form of
exec() to run the program /bin/ls. See if you can try all of the
variants of exec(), including (on Linux) execl(), execle(),
execlp(), execv(), execvp(), and execvpe(). Why do
you think there are so many variants of the same basic call?

    - A: There are so many options for `exec()` since there are different use-cases.
        - When we know the number of arguments in advance, we should use functions with suffix `l`, i.e. `execl(), execlp(), execle()`; here `l` stands for list.
        - If the number of arguments is variable, we should use functions with suffix `v`: `execv(), execvp(), execve()`; here `v` stands for vector.
        - When using functions with suffix `p` like `execlp(), execvp()` the first argument is resolved using not only local directory but also `PATH` environment variable, i.e. we can pass not only direct path `/bin/ls` but also `ls` is valid.
        - When using functions with suffix `e` `execle(), execve()`, last argument is a vector of environment variables.

        For our task `execlp()` is the best choice since we can pass `ls` as first argument and also number of arguments is known in advance.

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include <unistd.h>

        int main(int argc, char *argv[]) {
            int rc = fork();
            if (rc < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
            } else if (rc == 0) {
                if (argc == 1) {
                    fprintf(stderr, "too little number of arguments\n");
                    exit(1);
                } else {
                    execlp("ls", "ls", argv[1], NULL);
                }
            }
        }
        ```

        ```sh
        prompt> gcc code/q4.c -o bin/q4
        prompt> ./bin/q4 .             
        Homework-code.md        README-fork.md          README.md               code                    generator.py                                                                                     
        Homework-simulation.md  README-generator.md     bin                     fork.py
        ```

5.  - Q: Now write a program that uses wait() to wait for the child process
to finish in the parent. What does wait() return? What happens if
you use wait() in the child?

    - A: Calling `wait()` in parent returns process id of the process that has been finished, calling `wait()` in a child returns -1, since there are no children processes to wait.

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <unistd.h>

        int main() {
            int rc = fork();
            if (rc < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
            } else {
                char *loc = (rc == 0) ? "child" : "parent";
                pid_t pid = wait(NULL);
                printf("%s: rc = %d, wait() has returned %d\n", loc, rc, pid);
            }
        }
        ```

        ```sh
        prompt> gcc code/q5.c -o bin/q5
        prompt> ./bin/q5
        child: rc = 0, wait() has returned -1
        parent: rc = 8342, wait() has returned 8342
        ```

6.  - Q: Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be
useful?
    - A: `waitpid()` is useful when there are few `fork()` calls from the main process and there is need to synchronize waiting for each of them. Example:

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <unistd.h>

        int main() {
            const int N = 5;
            int i, rcs[N];
            for (i = 0; i < N; i++) {
                int rc = fork();
                if (rc < 0) {
                    fprintf(stderr, "fork failed\n");
                    exit(1);
                } else if (rc == 0) {
                    sleep(i);
                    exit(0);
                } else {
                    rcs[i] = rc;
                }
            }

            for (i = 0; i < N; i++) {
                waitpid(rcs[i], NULL, 0);
                printf("child with pid:%d has finished\n", rcs[i]);
            }
        }
        ```

        ```sh
        prompt> gcc code/q6.c -o bin/q6
        prompt> ./bin/q6
        child with pid:16212 has finished
        child with pid:16213 has finished
        child with pid:16214 has finished
        child with pid:16215 has finished
        child with pid:16216 has finished
        ```

7.  - Q: Write a program that creates a child process, and then in the child
closes standard output (STDOUT_FILENO). What happens if the child
calls printf() to print some output after closing the descriptor?

    - A: After closing standart output, printing to stdout is equal to no-op.

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <unistd.h>

        int main() {
            int rc = fork();
            if (rc < 0) {
                fprintf(stderr, "fork failed\n");
                exit(1);
            } else if (rc == 0) {
                close(STDOUT_FILENO);
                printf("writing to stdout\n");
            }
        }
        ```

        ```sh
        prompt> gcc ./code/q7.c -o ./bin/q7
        prompt> ./bin/q7
        ```

8.  - Q: Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the
pipe() system call.

    - A: For demonstration reasons we'll use `ls` as an output command and `wc -l` as an input command, so we'll pipe listing a content of current directory followed by counting number of lines in it; this result will be displayed to standart output of the pipeline.

        ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <unistd.h>

        int main() {
            int pipefd[2];
            pid_t cpid1, cpid2;

            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            cpid1 = fork();
            if (cpid1 == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (cpid1 == 0) {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
                execlp("ls", "ls", NULL);

                perror("execlp");
                exit(EXIT_FAILURE);
            } 

            cpid2 = fork();
            if (cpid2 == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (cpid2 == 0) {
                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
                execlp("wc", "wc", "-l", NULL);

                perror("execlp");
                exit(EXIT_FAILURE);
            } 

            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
        }
        ```

        ```sh
        prompt> gcc code/q8.c -o ./bin/q8
        prompt> ./bin/q8
               9
        ```
