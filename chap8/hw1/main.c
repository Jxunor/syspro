#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s [option] [env_name]\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 3) {
            char *value = getenv(argv[2]);
            if (value)
                printf("%s = %s\n", argv[2], value);
            else
                printf("no such environment variable: %s\n", argv[2]);
        } else {
            char **env;
            for (env = environ; *env != NULL; env++)
                printf("%s\n", *env);
        }
    }

    else if (strcmp(argv[1], "-u") == 0) {
        uid_t ruid = getuid();
        uid_t euid = geteuid();
        struct passwd *rp = getpwuid(ruid);
        struct passwd *ep = getpwuid(euid);
        printf("My Realistic User ID  : %d(%s)\n", ruid, rp ? rp->pw_name : "unknown");
        printf("My Valid User ID      : %d(%s)\n", euid, ep ? ep->pw_name : "unknown");
    }

    else if (strcmp(argv[1], "-g") == 0) {
        gid_t rgid = getgid();
        gid_t egid = getegid();
        struct group *rg = getgrgid(rgid);
        struct group *eg = getgrgid(egid);
        printf("My Realistic Group ID : %d(%s)\n", rgid, rg ? rg->gr_name : "unknown");
        printf("My Valid Group ID     : %d(%s)\n", egid, eg ? eg->gr_name : "unknown");
    }

    else if (strcmp(argv[1], "-i") == 0) {
        printf("my process number : [%d]\n", getpid());
    }

    else if (strcmp(argv[1], "-p") == 0) {
        printf("my parent's process number : [%d]\n", getppid());
    }

    else {
        fprintf(stderr, "invalid option: %s\n", argv[1]);
        exit(1);
    }

    return 0;
}
