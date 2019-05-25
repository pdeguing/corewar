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
		return strdup("incorrect file extension");
	}
	if (name[len - 1] != 's' || name[len - 2] != '.')
	{
		return strdup("incorrect file extension");
	}
	return NULL;
}

t_error		parser(char *name)
{
	int	fd;
	char	*champName;
	char	*champComment;
	char	*champContent;

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
	err = getName(&champName, fd);
	if (err)
	{
		return err;
	}
	err = getComment(&champComment, fd);
	if (err)
	{
		return err;
	}
	err = getContent(&champContent, fd);
	if (err)
	{
		return err;
	}
	return NULL;
}

t_error		assembler(char *name)
{
	t_error	err;

	err = parser(name);
	if (err)
	{
		return err;
	}
	return NULL;
}
