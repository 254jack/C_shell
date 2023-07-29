#include "shell.h"
/**
 * setenv_cmd - a function that sets a variable value
 * @argv: argument venctor
 */
int setenv_cmd(char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL)
	{
		fprintf(stderr, "setenv");
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

int cd_cmd(char **argv)
{
	char *home = getenv("HOME");
	char *ppwd = getenv("PWD");
	char *cpwd;
	char cwd[1024];

	if (argv[1] == NULL)
	{
		chdir(home);
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		chdir(ppwd);
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			perror("cd");
			return 1;
		}
	}

	getcwd(cwd, sizeof(cwd));
	cpwd = cwd;
	setenv("ppwd", ppwd, 1);
	setenv("PWD", cpwd, 1);

	return 0;
}
/**
 * r_vars - a function that searches for variables and replaces their names
 * @argv: argument vector
 * @env: environment variable
 */
void r_vars(char **argv, int status)
{
	char e_status[16];
	char pidStr[16];
	int i;

	snprintf(e_status, sizeof(e_status), "%d", WEXITSTATUS(status));
	setenv("?", e_status, 1);

	snprintf(pidStr, sizeof(pidStr), "%d", getppid());
	setenv("$", pidStr, 1);

	for (i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '$')
		{
			char *varName = argv[i] + 1;
			if (strcmp(varName, "?") == 0)
			{
				argv[i] = e_status;
			}
			else if (strcmp(varName, "$") == 0)
			{
				argv[i] = pidStr;
			}
			else
			{
				char *varValue = getenv(varName);
				if (varValue != NULL)
				{
					argv[i] = varValue;
				}
				else
				{
					argv[i] = "";
				}
			}
		}
	}
}
