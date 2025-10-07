#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;
    char buf;
    char savedText[100][200];
    int line = 0, col = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("File Open Error");
        exit(1);
    }

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

    printf("File read success\n");
    printf("Total Line : %d\n", totalLine);
    printf("You can choose 1 ~ %d Line\n", totalLine);
    printf("Pls 'Enter' the line to select : ");

    char input[50];
    scanf("%s", input);

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < totalLine; i++)
            printf("%s\n", savedText[i]);
    } else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        if (start < 1) start = 1;
        if (end > totalLine) end = totalLine;
        for (int i = start - 1; i < end; i++)
            printf("%s\n", savedText[i]);
    } else if (strchr(input, ',') != NULL) {
        char *token = strtok(input, ",");
        while (token != NULL) {
            int num = atoi(token);
            if (num > 0 && num <= totalLine)
                printf("%s\n", savedText[num - 1]);
            token = strtok(NULL, ",");
        }
    } else {
        int num = atoi(input);
        if (num >= 1 && num <= totalLine)
            printf("%s\n", savedText[num - 1]);
    }

    return 0;
}
