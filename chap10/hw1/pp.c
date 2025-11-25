#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **top, int data) {
    struct node *p = malloc(sizeof(struct node));
    if (!p) exit(1);
    p->data = data;
    p->next = *top;
    *top = p;
}

int delete(struct node **top) {
    if (*top == NULL)
        return -1;

    struct node *p = *top;
    int val = p->data;

    *top = p->next;
    free(p);

    return val;
}

int main() {
    struct node *top = NULL;
    int x;

    while (1) {
        if (scanf("%d", &x) != 1 || x <= 0) {
            printf("Print stack\n");
            while (top != NULL) {
                int v = delete(&top);
                if (v != -1)
                    printf("%d\n", v);
            }
            break;
        }
        addq(&top, x);
    }

    return 0;
}
