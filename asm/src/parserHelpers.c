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

	(void)dst;
	(void)fd;
}

/*
** Reads second line of file described by fd and feeds result into dst.
*/
t_error		getComment(char **dst, int fd)
{
	t_error		err;

	(void)dst;
	(void)fd;
}

/*
** Reads file line per line until EOF and feeds concatenation of all into
** dst.
*/
t_error		getContent(char **dst, int fd)
{
	t_error		err;

	(void)dst;
	(void)fd;
}
