#include "shell.h"

/**
 * make_env - Make the shell environment from the environment passed to main.
 * @env: Environment passed to main.
 *
 * Return: Pointer to the new environment.
 */
char **make_env(char **env)
{
	char **newenv = NULL;
	size_t i;

	for (i = 0; env[i] != NULL; i++)
		;

	newenv = malloc(sizeof(char *) * (i + 1));

	if (newenv == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}

	for (i = 0; env[i] != NULL; i++)
		newenv[i] = _strdup(env[i]);

	newenv[i] = NULL;

	return (newenv);
}

/**
 * free_env - Free the shell's environment.
 * @env: Shell's environment.
 *
 * Return: Void.
 */
void free_env(char **env)
{
	unsigned int i;

	for (i = 0; env[i] != NULL; i++)
		free(env[i]);

	free(env);
}
