#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char level[10];
    char message[64];
    struct Node *next;
} Node;

long long current_ns() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

Node* create_logs(int n) {
    Node *head = NULL, *tail = NULL;

    for (int i = 0; i < n; i++) {
        Node *node = malloc(sizeof(Node));

        if (i % 10 == 0)
            strcpy(node->level, "ERROR");
        else
            strcpy(node->level, "INFO");

        strcpy(node->message, "Server event log message");
        node->next = NULL;

        if (head == NULL)
            head = node;
        else
            tail->next = node;

        tail = node;
    }

    return head;
}

int analyze(Node *head) {
    int errors = 0;

    while (head) {
        if (strcmp(head->level, "ERROR") == 0)
            errors++;
        head = head->next;
    }

    return errors;
}

void free_logs(Node *head) {
    while (head) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int n = 1000000;

    long long start = current_ns();

    Node *logs = create_logs(n);
    int errors = analyze(logs);

    long long end = current_ns();

    printf("Baseline Errors: %d\n", errors);
    printf("Baseline Time: %.3f ms\n", (end - start) / 1000000.0);

    free_logs(logs);
    return 0;
}