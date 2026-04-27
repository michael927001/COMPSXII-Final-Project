#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char level[10];
    char message[64];
} Log;

long long current_ns() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

Log* create_logs(int n) {
    Log *logs = malloc(sizeof(Log) * n);

    for (int i = 0; i < n; i++) {
        if (i % 10 == 0)
            strcpy(logs[i].level, "ERROR");
        else
            strcpy(logs[i].level, "INFO");

        strcpy(logs[i].message, "Server event log message");
    }

    return logs;
}

int analyze(Log *logs, int n) {
    int errors = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(logs[i].level, "ERROR") == 0)
            errors++;
    }

    return errors;
}

int main() {
    int n = 1000000;

    long long start = current_ns();

    Log *logs = create_logs(n);
    int errors = analyze(logs, n);

    long long end = current_ns();

    printf("Optimized Errors: %d\n", errors);
    printf("Optimized Time: %.3f ms\n", (end - start) / 1000000.0);

    free(logs);
    return 0;
}