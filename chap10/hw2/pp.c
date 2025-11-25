#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *p = malloc(sizeof(struct node));
    if (!p) exit(1);
    p->data = data;
    p->next = NULL;

    if (*tail == NULL) {
        *head = p;
        *tail = p;
    } else {
        (*tail)->next = p;
        *tail = p;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL)
        return -1;

    struct node *p = *head;
    int val = p->data;

    *head = p->next;
    if (*head == NULL)
        *tail = NULL;

    free(p);
    return val;
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    int x;

    while (1) {
        if (scanf("%d", &x) != 1 || x <= 0) {
            printf("Print queue\n");
            while (head != NULL) {
                int v = delete(&head, &tail);
                printf("%d\n", v);
            }
            break;
        }
        addq(&head, &tail, x);
    }

    return 0;
}
