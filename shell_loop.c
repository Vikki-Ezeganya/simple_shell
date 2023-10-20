#include "shell.h"

/**
 * hsh - hsh
 * @infom:infom
 * @avct: 0 OR 1
 */
int hsh(info_t *infom, char **avct)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		_clear_info(infom);
		if (interactive(infom))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(infom);
		if (r != -1)
		{
			_set_info(infom, avct);
			builtin_ret = find_builtin(infom);
			if (builtin_ret == -1)
				find_cmd(infom);
		}
		else if (interactive(infom))
			_putchar('\n');
		_free_info(infom, 0);
	}
	write_history(infom);
	_free_info(infom, 1);
	if (!interactive(infom) && infom->status)
		exit(infom->status);
	if (builtin_ret == -2)
	{
		if (infom->err_num == -1)
			exit(infom->status);
		exit(infom->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds builtin
 * @infom: the parameter & return info struct
 * Return: -1 or 0 or 1 or -2
 */
int find_builtin(info_t *infom)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", mysetenv},
		{"unsetenv", myunset_env},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(infom->argv[0], builtintbl[i].type) == 0)
		{
			infom->line_count++;
			built_in_ret = builtintbl[i].func(infom);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - find command
 * @infom: infom
 * Return: void
 */
void find_cmd(info_t *infom)
{
	char *path = NULL;
	int i, k;

	infom->path = infom->argv[0];
	if (infom->linecount_flag == 1)
	{
		infom->line_count++;
		infom->linecount_flag = 0;
	}
	for (i = 0, k = 0; infom->arg[i]; i++)
		if (!is_delim(infom->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(infom, get_env(infom, "PATH="), infom->argv[0]);
	if (path)
	{
		infom->path = path;
		fork_cmd(infom);
	}
	else
	{
		if ((interactive(infom) || get_env(infom, "PATH=")
			|| infom->argv[0][0] == '/') && is_cmd(infom, infom->argv[0]))
			fork_cmd(infom);
		else if (*(infom->arg) != '\n')
		{
			infom->status = 127;
			print_error(infom, "not found\n");
		}
	}
}

/**
 * fork_cmd - fork command
 * @infom: infom
 * Return: void
 */
void fork_cmd(info_t *infom)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infom->path, infom->argv, get_environ(infom)) == -1)
		{
			_free_info(infom, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(infom->status));
		if (WIFEXITED(infom->status))
		{
			infom->status = WEXITSTATUS(infom->status);
			if (infom->status == 126)
				print_error(infom, "Permission denied\n");
		}
	}
}
