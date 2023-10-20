
#include "shell.h"

/**
 * get_history_file - get_history_file
 * @infom: infom
 * Return: string
 */
char *get_history_file(info_t *infom)
{
	char *buff, *dirct;
	dirct = get_env(infom, "HOME=");
	if (!dirct)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirct) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirct);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - write_history
 * @info: info
 * Return: 1 || -1
 */
int write_history(info_t *infom)
{
	ssize_t fd;
	char *filenamee = get_history_file(infom);
	list_t *node = NULL;

	if (!filenamee)
		return (-1);

	fd = open(filenamee, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenamee);
	if (fd == -1)
		return (-1);
	for (node = infom->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - read_history
 * @infom: infom
 * Return: count or  0 otherwise
 */
int read_history(info_t *infom)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(infom);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(infom, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(infom, buf + last, linecount++);
	free(buf);
	infom->histcount = linecount;
	while (infom->histcount-- >= HIST_MAX)
		delete_node_at_index(&(infom->history), 0);
	renumber_history(infom);
	return (infom->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @infom: infom
 * @buffer: buffer
 * @lcount: lcount
 * Return:  0
 */
int build_history_list(info_t *infom, char *buffer, int lcount)
{
	list_t *node = NULL;

	if (infom->history)
		node = infom->history;
	add_node_end(&node, buffer, lcount);

	if (!infom->history)
		infom->history = node;
	return (0);
}

/**
 * renumber_history -renumber_history
 * @infom: infom
 * Return: count
 */
int renumber_history(info_t *infom)
{
	list_t *node = infom->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (infom->histcount = i);
}
