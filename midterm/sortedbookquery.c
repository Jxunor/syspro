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

int compare(const void *a, const void *b) {
    Book *ba = (Book *)a;
    Book *bb = (Book *)b;
    return bb->borrow_count - ba->borrow_count;
}

int main() {
    FILE *fp;
    Book books[100];
    Book b;
    int mode, count = 0;

    fp = fopen("db.dat", "rb");

    printf("--bookquery--\n");
    printf("0: list of all books, 1: list of borrowed books ) ");
    scanf("%d", &mode);

    while (fread(&b, sizeof(b), 1, fp) == 1)
        books[count++] = b;
    fclose(fp);

    qsort(books, count, sizeof(Book), compare);

    printf("  id   bookname     author   year  numofborrow borrow\n");
    for (int i = 0; i < count; i++) {
        if (mode == 0 || (mode == 1 && books[i].is_borrowed == 1)) {
            printf("%4d %10s %10s %6d %12d %s\n",
                   books[i].id, books[i].title, books[i].author,
                   books[i].year, books[i].borrow_count,
                   books[i].is_borrowed ? " True" : "False");
        }
    }

    return 0;
}
