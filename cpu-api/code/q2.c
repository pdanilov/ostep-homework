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
