#include "shell.h"

/**
 * _clear_info - _clear_info
 * @infom: struct address
 */
void _clear_info(info_t *infom)
{
	infom->arg = NULL;
	infom->argv = NULL;
	infom->path = NULL;
	infom->argc = 0;
}

/**
 * _set_info - _set_info
 * @infom: infom
 * @avct: arg vector
 */
void _set_info(info_t *infom, char **avct)
{
	int i = 0;

	infom->fname = avct[0];
	if (infom->arg)
	{
		infom->argv = strtow(infom->arg, " \t");
		if (!infom->argv)
		{

			infom->argv = malloc(sizeof(char *) * 2);
			if (infom->argv)
			{
				infom->argv[0] = _strdup(infom->arg);
				infom->argv[1] = NULL;
			}
		}
		for (i = 0; infom->argv && infom->argv[i]; i++)
			;
		infom->argc = i;

		replace_alias(infom);
		replace_vars(infom);
	}
}

/**
 * _free_info - _free_info
 * @infom: struct address
 * @allf: true if freeing all fields
 */
void _free_info(info_t *infom, int allf)
{
	ffree(infom->argv);
	infom->argv = NULL;
	infom->path = NULL;
	if (allf)
	{
		if (!infom->cmd_buf)
			free(infom->arg);
		if (infom->env)
			free_list(&(infom->env));
		if (infom->history)
			free_list(&(infom->history));
		if (infom->alias)
			free_list(&(infom->alias));
		ffree(infom->environ);
			infom->environ = NULL;
		bfree((void **)infom->cmd_buf);
		if (infom->readfd > 2)
			close(infom->readfd);
		_putchar(BUF_FLUSH);
	}
}
