#include "shell.h"
void h_exit(char *cmd)
{
    if (strcmp(cmd, "exit") == 0)
    {
        char *stat = strtok(NULL, " ");
        if (stat != NULL)
        {
            int status = atoi(stat);
            free(cmd);
            exit(status);
        }
        else
        {
            free(cmd);
            exit(EXIT_SUCCESS);
        }
    }
}
