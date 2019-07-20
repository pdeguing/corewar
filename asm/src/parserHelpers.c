#include <assembler.h>

/*
** Reads first line of file described by fd and feeds result into dst.
*/

t_error		getName(char **dst, int fd)
{
	int			size;
	char		*line;
	char		*name;
	char		*tmp;

	line = NULL;
	get_next_line(fd, &line);
	while (*line == COMMENT_CHAR || !*line)
	{
		free(line);
		get_next_line(fd, &line);
	}
	tmp = line;
	while (*line && *line != '"')
		line++;
	if (*line)
		line++;
	size = ft_strlen(line) - 1;
	if (size < 0 || line[size] != '"' || size > PROG_NAME_LENGTH + 1)
	{
		free(tmp);
		return (ft_strdup(RED"Name not valid"RESET));
	}
	name = ft_strsub(line, 0, size);
	*dst = name;
	free(tmp);
	return NULL;
}

/*
** Reads second line of file described by fd and feeds result into dst.
*/

t_error		getComment(char **dst, int fd)
{
	int			size;
	char		*line;
	char		*comment;
	char		*tmp;

	line = NULL;
	get_next_line(fd, &line);
	while (*line == COMMENT_CHAR || !*line)
	{
		free(line);
		get_next_line(fd, &line);
	}
	tmp = line;
	while (*line && *line != '"')
		line++;
	if (*line)
		line++;
	size = ft_strlen(line) - 1;
	if (size < 0 || line[size] != '"' || size > COMMENT_LENGTH + 1)
	{
		free(tmp);
		return ft_strdup(RED"Comment not valid"RESET);
	}
	comment = ft_strsub(line, 0, size);
	*dst = comment;
	free(tmp);
	return (NULL);
}

/*
** Reads file line per line until EOF and feeds concatenation of all into
** dst.
*/

t_error		getContent(char **dst, int fd)
{
	char		*content;
	char		*tmp;

	content = ft_strdup("");
	while (get_next_line(fd, &tmp) > 0)
		content = ft_strjoinfree1(ft_strjoinfree2(content, tmp), "\n");
	*dst = content;
	return (NULL);
}
