#include "shell.h"

/**
 * h_exit - a function that handles exit command
 * @cmd: command
 */
void h_exit(char *cmd)
{
	if (strncmp(cmd, "exit ", 5) == 0)
	{
		int status;
		char *arg = cmd + 5;
		int isNumeric = 1;
		size_t arglen = strlen(arg);
		size_t i;

		for (i = 0; i < arglen; i++)
		{
			if (!isdigit((unsigned char)arg[i]))
			{
				isNumeric = 0;
				break;
			}
		}

		if (isNumeric)
		{
			status = atoi(arg);
			free(cmd);
			_Exit(status);
		}
		else
		{
			fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", arg);
			free(cmd);
			_Exit(2);
		}
	}
	else if (strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		_Exit(EXIT_SUCCESS);
	}
}

/**
 * g_ddir - a helper function to get the default directory
 * @arg: argument
 * Return: the default directory
 */
char *g_ddir(char *arg)
{
    char *ddir = getenv("HOME");
	(void)arg;

    if (!ddir)
    {
        fprintf(stderr, "cd: could not determine the home directory\n");
        return NULL;
    }

    return ddir;
}

/**
 * h_old_dir - a helper function to handle the previous directory argument
 * @old_dir: previous directory
 * @arg: argument
 * Return: the previous directory or NULL if it doesn't exist
 */
char *h_old_dir(char *old_dir, char *arg)
{
	(void)arg;
    if (old_dir[0] == '\0')
    {
        fprintf(stderr, "cd: no previous directory\n");
        return NULL;
    }

    return old_dir;
}

/**
 * c_d - a helper function to change the current directory
 * @arg: argument
 * @old_dir: previous directory
 * @new_dir: current directory
 * Return: 1 on success, 0 on failure
 */
int c_d(char *arg, char *old_dir, char *new_dir)
{
    if (getcwd(old_dir, PATH_MAX) == NULL)
    {
        perror("cd: getcwd failed");
        return 0;
    }

    if (chdir(arg) == -1)
    {
        perror("cd");
        return 0;
    }

    if (getcwd(new_dir, PATH_MAX) == NULL)
    {
        perror("cd: getcwd failed");
        return 0;
    }

    return 1;
}

/**
 * h_cd - a function that handles the cd command
 * @cmd: command
 * @old_dir: previous directory
 * @new_dir: current directory
 */
void h_cd(char *cmd, char *old_dir, char *new_dir)
{
    if (strncmp(cmd, "cd ", 3) == 0)
    {
        char *arg = cmd + 3;

        if (arg[0] == '\0')
        {
            arg = g_ddir(arg);
            if (!arg)
            {
                return;
            }
        }
        else if (strcmp(arg, "-") == 0)
        {
            arg = h_old_dir(old_dir, arg);
            if (!arg)
            {
                return;
            }
        }

        if (c_d(arg, old_dir, new_dir))
        {
            if (setenv("PWD", new_dir, 1) != 0)
            {
                perror("cd: setenv failed");
                return;
            }
        }
    }
}
