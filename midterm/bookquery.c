#include <stdio.h>
#include <stdlib.h>

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
    int mode;

    fp = fopen("db.dat", "rb");

    printf("--bookquery--\n");
    printf("0: list of all books, 1: list of available books ) ");
    scanf("%d", &mode);
    printf("  id   bookname     author   year  numofborrow borrow\n");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (mode == 0 || (mode == 1 && b.is_borrowed == 1)) {
            printf("%4d %10s %10s %6d %12d %s\n", b.id, b.title, b.author, b.year, b.borrow_count, b.is_borrowed ? " True" : "False");
        }
    }

    fclose(fp);
    return 0;
}
