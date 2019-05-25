/**
 * File              : assembler.c
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#include "assembler.h"

/*
** Verifies that the filename is valid with .s extension.
*/
t_error		verifyFilename(char *filename)
{
	int	len;

	len = strlen(filename);
	if (len <= 3)
	{
		return strdup("file name too short");
	}
	if (filename[len - 1] != 's' || filename[len - 2] != '.')
	{
		return strdup("incorrect file extension");
	}
	return NULL;
}

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

/*
** Fills the champ struct with the content of file described by fd.
*/
t_error		fillChamp(t_champ *champ, int fd)
{
	t_error		err;

	err = getName(&champ->name, fd);
	if (err)
	{
		return err;
	}
	err = getComment(&champ->comment, fd);
	if (err)
	{
		return err;
	}
	err = getContent(&champ->content, fd);
	if (err)
	{
		return err;
	}
	return NULL;
}

/*
** Parses the file into a t_champ struct, does various verifications of input
** and returns err in case of error.
*/
t_error		parser(t_champ *champ, char *filename)
{
	int	fd;

	err = verifyFilename(filename)
	if (err)
	{
		return err;	
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		return strerror(errno);
	}
	err = fillChamp(champ, fd);
	if (err)
	{
		return err;
	}
	return NULL;
}

/*
** Transforms the t_champ struct into a list of instructions, verifies
** that instructions are valid and returns err if they are not.
*/
t_error		lexer(t_champ *champ)
{
	(void)champ;
	return NULL;
}

/*
** Sets all members of t_champ struct to NULL.
*/
void		initChamp(t_champ *champ)
{
	champ->name = NULL;
	champ->comment = NULL;
	champ->content = NULL;
}

/*
** Translates assembly source file into a binary file for Corewar virtual
** machine.
*/
t_error		assembler(char *filename)
{
	t_error	err;
	t_champ	champ;

	initChamp(&champ);
	err = parser(&champ, filename);
	if (err)
	{
		return err;
	}
	err = lexer(champ);
	if (err)
	{
		return err;
	}
	return NULL;
}
