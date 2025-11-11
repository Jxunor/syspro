#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char c;
    FILE *fp1 = NULL, *fp2 = NULL;

    if (argc != 4) {
        fprintf(stderr, "How to use: %s MODE FILE1 FILE2\n", argv[0]);
		return 1;
    }

    fp1 = fopen(argv[2], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[2]);
        return 2;
    }

    fp2 = fopen(argv[3], "w");
    if (fp2 == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[3]);
        fclose(fp1);
        return 3;
    }

    if (strcmp(argv[1], "0") == 0) {
        while ((c = fgetc(fp1)) != EOF)
            fputc(c, fp2);
    } else if (strcmp(argv[1], "1") == 0) {
        while ((c = fgetc(fp1)) != EOF)
            fputc(tolower((unsigned char)c), fp2);
	} else if (strcmp(argv[1], "2") == 0) {
		while ((c = fgetc(fp1)) != EOF)
			fputc(toupper((unsigned char)c), fp2);
    } else {
		fprintf(stderr, "error");
        fclose(fp1);
        fclose(fp2);
		exit(1);
    }

    fclose(fp1);
	fclose(fp2);

	fp2 = fopen(argv[3], "r");
	c = getc(fp2);
	while (c != EOF) {
		putc(c, stdout);
		c = getc(fp2);
	}

	fclose(fp2);
    return 0;
}
