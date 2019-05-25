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
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef char*			t_error;

struct				s_champ
{
	char			*name;
	char			*comment;
	char			*content;
};

typedef struct s_champ		t_champ;

#endif
