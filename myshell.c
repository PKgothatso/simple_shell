#include "shell.h"

void process_input(vars_t *vars);
void clean_up(vars_t *vars);

/**
 * main - Main function for the shell.
 * @argc: Number of arguments passed to main.
 * @argv: Array of arguments passed to main.
 * @environment: Array of environment variables.
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0;
	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.argv = argv;
	vars.env = make_env(environment);
	signal(SIGINT, sig_handler);

	if (!isatty(STDIN_FILENO))
		is_pipe = 1;

	if (is_pipe == 0)
		_puts("$ ");

	sig_flag = 0;

	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		process_input(&vars);
		clean_up(&vars);
	}

	if (is_pipe == 0)
		_puts("\n");

	free_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}

/**
 * process_input - Process user input.
 * @vars: Pointer to vars_t struct.
 */
void process_input(vars_t *vars)
{
	unsigned int i;

	sig_flag = 1;
	vars->count++;
	vars->commands = tokenize(vars->buffer, ";");

	for (i = 0; vars->commands && vars->commands[i] != NULL; i++)
	{
		vars->av = tokenize(vars->commands[i], "\n \t\r");

		if (vars->av && vars->av[0])
		{
			void (*builtin_func)(vars_t *) = check_for_builtins(vars);
			if (builtin_func == NULL)

				check_for_path(vars);
		}

		free(vars->av);
	}
}

/**
 * clean_up - Clean up resources.
 * @vars: Pointer to vars_t struct.
 */
void clean_up(vars_t *vars)
{
	sig_flag = 0;
	if (is_pipe == 0)
		_puts("$ ");

	free(vars->buffer);
	free(vars->commands);
	vars->buffer = NULL;
}
