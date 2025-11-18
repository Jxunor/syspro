#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 64

int main() {
    char line[MAXLINE];
    char *args[MAXARG];
    char *save;

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (!fgets(line, MAXLINE, stdin))
            break;

        line[strcspn(line, "\n")] = '\0';

        int bg = 0;
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '&') {
            bg = 1;
            line[len - 1] = '\0';
        }

        int idx = 0;
        char *token = strtok_r(line, " \t", &save);
        while (token && idx < MAXARG - 1) {
            args[idx++] = token;
            token = strtok_r(NULL, " \t", &save);
        }
        args[idx] = NULL;

        if (idx == 0)
            continue;

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("exec failed");
            exit(1);
        } else {
            if (!bg)
                waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
