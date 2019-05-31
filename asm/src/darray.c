#include <darray.h>

t_darray	*darray_append(t_darray *arr, void *item)
{
	if (arr->size >= arr->capacity)
	{
		arr = realloc(arr, arr->capacity + 100);
		arr->capacity += 100;
	}
	arr->content[arr->size] = item;
	arr->size++;
	return arr;
}

void		darray_init(t_darray *arr)
{
	if (!arr)
		return ;
	arr->content = NULL;
	arr->size = 0;
	arr->capacity = 0;
}
