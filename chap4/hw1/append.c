#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *src, *dest;
    int c;

    if (argc != 3)
        return 1;

    src = fopen(argv[1], "r");
    if (src == NULL)
        return 1;

    dest = fopen(argv[2], "a");
    if (dest == NULL) {
        fclose(src);
        return 1;
    }

    while ((c = fgetc(src)) != EOF)
        fputc(c, dest);

    fclose(src);
    fclose(dest);
    return 0;
}
