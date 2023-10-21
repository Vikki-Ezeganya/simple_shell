#include "shell.h"

/**
 * myenv - print environment
 * @info: info
 * Return: 0
 */
int myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - get_env
 * @info: info
 * @name: name
 * Return: value
 */
char *get_env(info_t *infor, const char *name)
{
	list_t *node = infor->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetenv - set_env
 * @infor: infor
 * Return: Always 0
 */
int mysetenv(info_t *infor)
{
	if (infor->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infor, infor->argv[1], infor->argv[2]))
		return (0);
	return (1);
}

/**
 * myunsetenv - Remove environment variable
 * @infor: infor
 *  Return: 0
 */
int myunset_env(info_t *infor)
{
	int i;

	if (infor->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= infor->argc; i++)
		_unsetenv(infor, infor->argv[i]);

	return (0);
}

/**
 * _populate_env_list - populates env linked list
 * @infor: infor
 * Return:  0
 */
int _populate_env_list(info_t *infor)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	infor->env = node;
	return (0);
}
