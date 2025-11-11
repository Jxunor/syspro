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

    fp = fopen("db.dat", "rb");

	printf("--bookquery--");
    printf("%-5s %-20s %-20s %-6s %-13s %-12s\n",
           "ID", "제목", "저자", "년도", "대여횟수", "대여중");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        printf("%-5d %-20s %-20s %-6d %-13d %-12s\n",
               b.id, b.title, b.author, b.year,
               b.borrow_count, b.is_borrowed ? "Yes" : "No");
    }

    fclose(fp);
    return 0;
}

