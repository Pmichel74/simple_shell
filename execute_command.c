#include "main.h"

/**
 * execute_command - Executes a command with given arguments
 * @args: Array of command arguments
 * @argv: Array of command arguments
 * @envp: Array of environment variables
 * @shell_name: Name of the shell program
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **args, char **envp, char *shell_name)
{
	char *command_path = NULL;
	struct stat st;

	if (!args || !args[0])
		return (-1);

	if (strcmp(args[0], "env") == 0)
	{
		print_env(envp);
		return (0);
	}

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (stat(args[0], &st) == 0 && st.st_mode & S_IXUSR)
			command_path = strdup(args[0]);
	}
	else
	{
		command_path = find_command(args[0], envp);
	}


	if (fork_and_execute(command_path, args, envp, shell_name) == -1)
	{
		free(command_path);
		return (-1);
	}

	free(command_path);
	return (0);
}
