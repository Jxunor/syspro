#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int id;
    char title[20];
    char author[20];
    int year;
    int borrow_count;
    int is_borrowed;
    struct Book *next;
} Book;

int main() {
    FILE *fp;
    Book *head = NULL, *newBook, *cur;

    while (1) {
        newBook = (Book *)malloc(sizeof(Book));
        if (scanf("%d %s %s %d %d %d",
                  &newBook->id, newBook->title, newBook->author,
                  &newBook->year, &newBook->borrow_count, &newBook->is_borrowed) != 6) {
            free(newBook);
            break;
        }

        newBook->next = NULL;

        if (head == NULL || newBook->year > head->year) {
            newBook->next = head;
            head = newBook;
        } else {
            cur = head;
            while (cur->next != NULL && cur->next->year >= newBook->year)
                cur = cur->next;
            newBook->next = cur->next;
            cur->next = newBook;
        }
    }

    fp = fopen("db.dat", "wb");
    for (cur = head; cur != NULL; cur = cur->next)
        fwrite(cur, sizeof(Book) - sizeof(Book *), 1, fp);
    fclose(fp);

    while (head != NULL) {
        cur = head;
        head = head->next;
        free(cur);
    }

    return 0;
}
