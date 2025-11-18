#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXLINE 1024
#define MAXARGS 64

void parse(char *cmd, char **argv) {
    while (*cmd != '\0') {
        while (*cmd == ' ' || *cmd == '\t')
            *cmd++ = '\0';
        *argv++ = cmd;
        while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
            cmd++;
    }
    *argv = NULL;
}

void run_cmd(char *cmd) {
    char *argv[MAXARGS];
    char *infile = NULL, *outfile = NULL;
    int bg = 0;

    int len = strlen(cmd);
    if (len > 0 && cmd[len - 1] == '&') {
        bg = 1;
        cmd[len - 1] = '\0';
    }

    char *out = strchr(cmd, '>');
    char *in  = strchr(cmd, '<');

    if (out) {
        *out = '\0';
        outfile = strtok(out + 1, " \t");
    }

    if (in) {
        *in = '\0';
        infile = strtok(in + 1, " \t");
    }

    parse(cmd, argv);

    pid_t pid = fork();
    if (pid == 0) {
        if (outfile) {
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if (infile) {
            int fd = open(infile, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        execvp(argv[0], argv);
        perror("exec error");
        exit(1);
    } else {
        if (!bg)
            waitpid(pid, NULL, 0);
    }
}

int main() {
    char line[MAXLINE];

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (!fgets(line, MAXLINE, stdin))
            break;

        line[strcspn(line, "\n")] = '\0';

        char *cmd = strtok(line, ";");
        while (cmd) {
            if (strlen(cmd) > 0)
                run_cmd(cmd);
            cmd = strtok(NULL, ";");
        }
    }

    return 0;
}
