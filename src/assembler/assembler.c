/**
 * File              : assembler.c
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#include "assembler.h"

t_error		verifyExtension(char *name)
{
	int	len;

	len = strlen(name);
	if (len <= 3)
	{
		return strdup("file name too short");
	}
	if (name[len - 1] != 's' || name[len - 2] != '.')
	{
		return strdup("incorrect file extension");
	}
	return NULL;
}

/*
** Parses the file into a t_champ struct, does various verifications of input
** and returns err in case of error.
*/
t_error		parser(t_champ *champ, char *name)
{
	int	fd;

	err = verifyExtension(name)
	if (err)
	{
		return err;	
	}
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		return strerror(errno);
	}
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
** Transforms the t_champ struct into a list of instructions, verifies
** that instructions are valid and returns err if they are not.
*/
t_error		lexer(t_champ *champ)
{
	(void)champ;
	return NULL;
}

void		initChamp(t_champ *champ)
{
	champ->name = NULL;
	champ->comment = NULL;
	champ->content = NULL;
}

t_error		assembler(char *name)
{
	t_error	err;
	t_champ	champ;

	initChamp(&champ);
	err = parser(&champ, name);
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
