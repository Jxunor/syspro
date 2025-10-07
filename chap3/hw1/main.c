#include <stdio.h>
#include "copy.h"

char line[MAXLINE];
char longest[MAXLINE];

int getline_custom(char s[], int lim) {
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

int main() {
    int len, max = 0, count = 0;

    while (count < 5 && (len = getline_custom(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(line, longest);
        }
        count++;
    }

    if (max > 0)
        printf("%s\n", longest);

    return 0;
}
