#include "shell.h"

/**
 * _realloc - Reallocates a pointer to double the space.
 * @ptr: Pointer to the old array.
 * @size: Pointer to the number of elements in the old array.
 *
 * Return: Pointer to the new array.
 */
char **_realloc(char **ptr, size_t *size)
{
	char **new
	size_t i;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		new[i] = ptr[i];
	}
	*size += 10;
	free(ptr);

	return (new);
}
