#ifndef SHELL_H
#define	SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <limits.h>

/**
 * struct variables - Represents the variables used in the shell.
 * @av: Command line arguments.
 * @buffer: Buffer for storing the entered command.
 * @env: Environment variables.
 * @count: Count of commands entered in the shell.
 * @argv: Arguments at the opening of the shell.
 * @status: Exit status of the last executed command.
 * @commands: Array of commands (provide a brief description).
 */
typedef struct variables
{
	char **av;
	char *buffer;
	char **argv;
	char **env;
	char **commands; /* If 'commands is not a member, remove this line. */
	int status;
	size_t count;
} vars_t;

/**
 * struct builtins - Represents a structure for built-in shell commands.
 * @name: Name of the built-in command.
 * @f: Pointer to the function corresponding to the built-in command.
 * @commands: Additional member in struct builtins.
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
	/* No 'commmands' member in the 'builtins' structure. */
} builtins_t;

/* Memory management functions */
char **make_env(char **env);
void free_env(char **env);

/* String manipulation functions */
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strdup(char *strtodup);
ssize_t _puts(char *str);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);

/* Tokenization functions */
char **tokenize(char *buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *new_strtok(char *str, const char *delim);

/*Builtin functions */
void (*check_for_builtins(vars_t *vars))(vars_t *);
void new_exit(vars_t * vars);
void _env(vars_t *vars);
void new_setenv(vars_t *vars);
void new_unsetenv(vars_t *vars);

/* Environment variable functions */
void add_key(vars_t *vars);
char **find_key(char **env, char *key);
char *add_value(char *key, char *value);
int _atoi(char *str);

/*Path-related functions*/
void check_for_path(vars_t *vars);
int path_execute(char *command, vars_t *vars);
char *find_path(char **env);
int evecute_cwd(vars_t *vars);
int check_for_dir(char *str);
int execute_cwd(vars_t *vars);
void sig_handler(int signo);

/*Error handling functions*/
void print_error(vars_t *vars, char *msg);
char *uitoa(unsigned int count);
void _puts2(char *str);

#endif /* SHELL_H */
