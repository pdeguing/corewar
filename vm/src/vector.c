#include <vector.h>

void		vector_init(t_vector *v)
{
	v->capacity = VECTOR_INIT_CAPACITY;
	v->size = 0;
	v->items = malloc(sizeof(void *) * v->capacity);
}

int		vector_size(t_vector *v)
{
	return v->size;
}

static void	vector_resize(t_vector *v, int capacity)
{
	void	**items;

	items = realloc(v->items, sizeof(void *) * capacity);
	if (items)
	{
		v->items = items;
		v->capacity = capacity;
	}
}

void		vector_add(t_vector *v, void *item)
{
	if (v->capacity == v->size)
		vector_resize(v, v->capacity * 2);
	v->items[v->size++] = item;
}

void		vector_set(t_vector *v, int index, void *item)
{
	if (index >= 0 && index < v->size)
		v->items[index] = item;
}

void		*vector_get(t_vector *v, int index)
{
	if (index >= 0 && index < v->size)
		return v->items[index];
	return NULL;
}

void		vector_delete(t_vector *v, int index)
{
	int	i;

	if (index < 0 || index >= v->size)
		return ;
	v->items[index] = NULL;
	i = index;
	while (i < v->size - 1)
	{
		v->items[i] = v->items[i + 1];
		v->items[i + 1] = NULL;
		i++;
	}
	v->size--;
	if (v->size > 0 && v->size == v->capacity / 4)
		vector_resize(v, v->capacity / 2);
}

void		vector_free(t_vector *v)
{
	free(v->items);
}
