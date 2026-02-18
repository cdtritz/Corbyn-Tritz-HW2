#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static void usage(const char *prog) {
    fprintf(stderr, "Coordinator: usage: %s <number> <f1> <f2> <f3> <f4>\n", prog);
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        usage(argv[0]);
        return 1;
    }

    // argv[1] = number (dividend)
    // argv[2..5] = candidate factors (divisors)
    const char *number = argv[1];

    for (int i = 2; i <= 5; i++) {
        const char *factor = argv[i];

        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("Coordinator: fork failed");
            return 1;
        }

        if (child_pid == 0) {
            // Child: replace with Checker
            // execlp(file, arg0, arg1, arg2, NULL)
            execlp("./checker", "checker", factor, number, (char *)NULL);

            // If exec returns, it failed
            perror("Coordinator: exec failed");
            _exit(1);
        } else {
            // Parent: print forked PID, then wait for that exact PID
            printf("Coordinator: forked process with ID %d.\n", (int)child_pid);
            printf("Coordinator: waiting for process [%d].\n", (int)child_pid);

            int status = 0;
            pid_t waited = waitpid(child_pid, &status, 0);
            if (waited < 0) {
                perror("Coordinator: waitpid failed");
                return 1;
            }

            if (WIFEXITED(status)) {
                int code = WEXITSTATUS(status);
                printf("Coordinator: child process %d returned %d.\n", (int)child_pid, code);
            } else if (WIFSIGNALED(status)) {
                int sig = WTERMSIG(status);
                // Not required by spec, but useful if something goes sideways.
                printf("Coordinator: child process %d terminated by signal %d.\n", (int)child_pid, sig);
            } else {
                printf("Coordinator: child process %d ended unexpectedly.\n", (int)child_pid);
            }
        }
    }

    printf("Coordinator: exiting.\n");
    return 0;
}
