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

	fp = fopen("db.dat", "ab");
	while (scanf("%d %s %s %d %d %d", &b.id, b.title, b.author, &b.year, &b.borrow_count, &b.is_borrowed) == 6)
		fwrite(&b, sizeof(b), 1, fp);

	fclose(fp);
	exit(0);
}
