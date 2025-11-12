#include <stdio.h>

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
    int mode, id;
    int action_done = 0;

    fp = fopen("db.dat", "r+b");

    printf("--bookupdate--\n");
    printf("0 bookId: borrow book, 1 bookId: return book ) ");
    scanf("%d %d", &mode, &id);

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (b.id == id) {
            if (mode == 0) {
                if (!b.is_borrowed) {
                    b.is_borrowed = 1;
                    b.borrow_count++;
                    fseek(fp, -sizeof(b), SEEK_CUR);
                    fwrite(&b, sizeof(b), 1, fp);
                    printf("You've got below book..\n");
                } else {
                    printf("You cannot borrow below book since it has been booked.\n");
                }
            } else if (mode == 1) {
                if (b.is_borrowed) {
                    b.is_borrowed = 0;
                    fseek(fp, -sizeof(b), SEEK_CUR);
                    fwrite(&b, sizeof(b), 1, fp);
                    printf("You've returned below book..\n");
                }
            }

            printf("  id   bookname     author   year  numofborrow borrow\n");
            printf("%4d %10s %10s %6d %12d %s\n",
                   b.id, b.title, b.author, b.year, b.borrow_count,
                   b.is_borrowed ? " True" : "False");
            action_done = 1;
            break;
        }
    }

    if (!action_done)
        printf("Book ID %d not found.\n", id);

    fclose(fp);
    return 0;
}
