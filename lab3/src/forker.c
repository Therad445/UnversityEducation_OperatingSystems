#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        char *args[] = {"./sequential_min_max", NULL};
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Child process ID: %d\n", pid);
    }
    return 0;
}