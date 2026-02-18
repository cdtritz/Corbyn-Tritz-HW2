#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Checker: usage: %s <divisor> <dividend>\n", argv[0]);
        return 0;
    }

    int divisor = atoi(argv[1]);
    int dividend = atoi(argv[2]);

    pid_t pid = getpid();
    printf("Checker process [%d]: Starting.\n", (int)pid);

    if (divisor <= 0 || dividend <= 0) {
        printf("Checker process [%d]: Invalid arguments.\n", (int)pid);
        printf("Checker process [%d]: Returning 0.\n", (int)pid);
        return 0;
    }

    if (dividend % divisor == 0) {
        printf("Checker process [%d]: %d *IS* divisible by %d.\n", (int)pid, dividend, divisor);
        printf("Checker process [%d]: Returning 1.\n", (int)pid);
        return 1; // nonzero if divisible
    } else {
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", (int)pid, dividend, divisor);
        printf("Checker process [%d]: Returning 0.\n", (int)pid);
        return 0;
    }
}
