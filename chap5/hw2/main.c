#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;
    char buf;
    char savedText[100][200];
    int line = 0, col = 0;

    if (argc < 2)
        exit(1);

    if ((fd = open(argv[1], O_RDONLY)) == -1)
        exit(1);

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[line][col] = '\0';
            line++;
            col = 0;
        } else {
            savedText[line][col++] = buf;
        }
    }
    savedText[line][col] = '\0';
    if (col == 0 && line > 0)
        line--;

    close(fd);

    int totalLine = line + 1;
    for (int i = totalLine - 1; i >= 0; i--)
        printf("%s\n", savedText[i]);

    return 0;
}
