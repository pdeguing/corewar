#ifndef DARRAY_H
# define DARRAY_H

#include <stdlib.h>

typedef struct			s_darray
{
	void			*content;
	size_t			size;
	size_t			capacity;
}				t_darray;

t_darray	darray_append(t_darray *arr, void *item);
void		darray_init(t_darray *arr);


#endif
