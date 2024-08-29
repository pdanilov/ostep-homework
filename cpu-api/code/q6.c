#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
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
