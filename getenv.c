#include "shell.h"

/**
 * get_environ - get_environ
 * @infom: infom
 * Return: 0
 */
char **get_environ(info_t *infom)
{
	if (!infom->environ || infom->env_changed)
	{
		infom->environ = list_to_strings(infom->env);
		infom->env_changed = 0;
	}

	return (infom->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @infom: infom
 *  Return: 1 for delete, 0 any
 * @envvar: the string env var property
 */
int _unsetenv(info_t *infom, char *envvar)
{
	list_t *node = infom->env;
	size_t i = 0;
	char *p;

	if (!node || !envvar)
		return (0);

	while (node)
	{
		p = starts_with(node->str, envvar);
		if (p && *p == '=')
		{
			infom->env_changed = delete_node_at_index(&(infom->env), i);
			i = 0;
			node = infom->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (infom->env_changed);
}

/**
 * _setenv - Initialize or modify environment variable,
 * @infom: infom
 * @varb: string env varb
 * @val: val
 *  Return: 0
 */
int _setenv(info_t *infom, char *varb, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!varb || !val)
		return (0);

	buf = malloc(_strlen(varb) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, varb);
	_strcat(buf, "=");
	_strcat(buf, val);
	node = infom->env;
	while (node)
	{
		p = starts_with(node->str, varb);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			infom->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(infom->env), buf, 0);
	free(buf);
	infom->env_changed = 1;
	return (0);
}
