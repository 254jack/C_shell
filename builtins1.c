#include "shell.h"
int setenv_cmd(char **argv)
{
    if (argv[1] == NULL || argv[2] == NULL)
    {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return 1;
    }

    if (setenv(argv[1], argv[2], 1) == -1)
    {
        perror("setenv");
        return 1;
    }

    return 0;
}

int unsetenv_cmd(char **argv)
{
    if (argv[1] == NULL)
    {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return 1;
    }

    if (unsetenv(argv[1]) == -1)
    {
        perror("unsetenv");
        return 1;
    }

    return 0;
}
