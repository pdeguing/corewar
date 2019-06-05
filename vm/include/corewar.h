#ifndef COREWAR_H
#define COREWAR_H

#include "op.h"
#include "vector.h"

typedef struct		s_champ
{
	header_t	infos;
	void		*program;
}			t_champ;

typedef struct		s_vm
{
	unsigned int	dump;
	t_vector	champs;
}			t_vm;
#endif
