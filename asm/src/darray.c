#include <darray.h>

t_darray	append(t_darray *array, void *item)
{
	if (array->elem >= array->size)
	{
		array = realloc(array, array->size + 100);
		array->size += 100;
	}
	array->array[array->elem] = item;
	array->elem++;
	return array;
}
