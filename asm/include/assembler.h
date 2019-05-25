/**
 * File              : assembler.h
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include "../../libft/includes/libft.h"
# include "op.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

typedef char*			t_error;

struct				s_champ
{
	char			*name;
	char			*comment;
	char			*content;
};

typedef struct s_champ		t_champ;

t_error		assembler(char *filename);
void		initChamp(t_champ *champ);
t_error		lexer(t_champ *champ);
t_error		verifyFilename(char *filename);
t_error		fillChamp(t_champ *champ, int fd);
t_error		parser(t_champ *champ, char *filename);
t_error		getName(char **dst, int fd);
t_error		getComment(char **dst, int fd);
t_error		getContent(char **dst, int fd);

#endif
