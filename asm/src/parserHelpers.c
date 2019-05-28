/**
 * File              : parserHelpers.c
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#include <assembler.h>

/*
** Reads first line of file described by fd and feeds result into dst.
*/
t_error		getName(char **dst, int fd)
{
	t_error		err;
	char		*line;
	char		*name;

	get_next_line(fd, &line);
	if (!(name = ft_strsplit(line, ' ')[1]) || name[0] != '"')
		return (err = "\x1b[91mName not valid.");
	name = ft_strsub(name, 1, ft_strlen(name) - 2);
	*dst = name;
	return NULL;
}

/*
** Reads second line of file described by fd and feeds result into dst.
*/
t_error		getComment(char **dst, int fd)
{
	t_error		err;
	char		*line;
	char		*comment;

	get_next_line(fd, &line);
	while (*line && *line != '"')
		line++;
	/*
	if (!(comment = ft_strsplit(line, ' ')[1]) || comment[0] != '"')
		return (err = "\x1b[91mComment not valid.");
		*/
	comment = ft_strsub(line, 1, ft_strlen(line) - 2);
	*dst = comment;
	return (NULL);
}

/*
** Reads file line per line until EOF and feeds concatenation of all into
** dst.
*/
t_error		getContent(char **dst, int fd)
{
	t_error		err;
	char		*content;
	char		*tmp;

	content = ft_strdup("");
	while (get_next_line(fd, &tmp) > 0)
		content = ft_strjoin(ft_strjoin(content, tmp), "\n");
	ft_putstr(content);
	*dst = content;
	return (NULL);
}
