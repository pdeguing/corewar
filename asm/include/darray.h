#ifndef DARRAY_H
# define DARRAY_H

typedef struct			s_darray
{
	void			*content;
	size_t			size;
	size_t			capacity;
}				t_darray;

t_darray	append(t_darray *arr, void *item);


#endif
