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
