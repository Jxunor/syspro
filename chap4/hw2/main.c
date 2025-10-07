#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int c, line = 1;
    int show_line = 0;
    int start = 1;

    if (argc < 2) {
        fp = stdin;
        while ((c = getc(fp)) != EOF)
            putchar(c);
        return 0;
    }

    if (strcmp(argv[1], "-n") == 0) {
        show_line = 1;
        start = 2;
    }

    for (int i = start; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL)
            continue;

        if (show_line)
            printf("%6d  ", line++);

        while ((c = getc(fp)) != EOF) {
            putchar(c);
            if (show_line && c == '\n' && !feof(fp))
                printf("%6d  ", line++);
        }

        fclose(fp);
    }

    return 0;
}
