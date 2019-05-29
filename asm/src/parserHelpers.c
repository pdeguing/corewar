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
	char		*line;
	char		*name;

	get_next_line(fd, &line);
	while (*line && *line != '"')
		line++;
	if (*line)
		line++;
	if (line[ft_strlen(line) - 1] != '"')
		return ft_strdup(RED"Comment not valid"RESET);
	name = ft_strsub(line, 0, ft_strlen(line) - 1);
	*dst = name;
	return NULL;
}

/*
** Reads second line of file described by fd and feeds result into dst.
*/
t_error		getComment(char **dst, int fd)
{
	char		*line;
	char		*comment;

	get_next_line(fd, &line);
	while (*line && *line != '"')
		line++;
	if (*line)
		line++;
	if (line[ft_strlen(line) - 1] != '"')
		return ft_strdup(RED"Comment not valid"RESET);
	comment = ft_strsub(line, 0, ft_strlen(line) - 1);
	*dst = comment;
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
		content = ft_strjoin(ft_strjoin(content, tmp), "\n");
	*dst = content;
	return (NULL);
}
