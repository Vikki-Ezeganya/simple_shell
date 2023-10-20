#include "shell.h"

/**
 * is_cmd - is_cmd
 * @infom: infom
 * @pathh: pathh
 * Return: 1 or 0
 */
int is_cmd(info_t *infom, char *pathh)
{
	struct stat st;

	(void)infom;
	if (!pathh || stat(pathh, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - dup_chars
 * @pathst: pathst
 * @startidx: startidx
 * @stopidx: stopidx
 * Return: pointer
 */
char *dup_chars(char *pathst, int startidx, int stopidx)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = startidx; i < stopidx; i++)
		if (pathst[i] != ':')
			buf[k++] = pathst[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - find_path
 * @infom: infom
 * @pathst: pathst
 * @cmdd: cmdd
 * Return: path
 */
char *find_path(info_t *infom, char *pathst, char *cmdd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathst)
		return (NULL);
	if ((_strlen(cmdd) > 2) && starts_with(cmdd, "./"))
	{
		if (is_cmd(infom, cmdd))
			return (cmdd);
	}
	while (1)
	{
		if (!pathst[i] || pathst[i] == ':')
		{
			path = dup_chars(pathst, curr_pos, i);
			if (!*path)
				_strcat(path, cmdd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmdd);
			}
			if (is_cmd(infom, path))
				return (path);
			if (!pathst[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return(NULL);
}
