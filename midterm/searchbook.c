#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[20];
    char author[20];
    int year;
    int borrow_count;
    int is_borrowed;
} Book;

int main() {
    FILE *fp;
    Book b;
    char search[20];
    int found = 0;

    printf("input name of book ) ");
    scanf("%s", search);

    fp = fopen("db.dat", "rb");
    if (fp == NULL) return 1;

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (strcmp(b.title, search) == 0) {
            if (!found) {
                printf("  id   bookname     author   year  numofborrow borrow\n");
                found = 1;
            }
            printf("%4d %10s %10s %6d %12d %s\n",
                   b.id, b.title, b.author, b.year, b.borrow_count,
                   b.is_borrowed ? " True" : "False");
        }
    }

    if (!found)
        printf("not found book name : '%s'\n", search);

    fclose(fp);
    return 0;
}
