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
