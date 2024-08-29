#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
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
