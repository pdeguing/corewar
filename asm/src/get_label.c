#include <assembler.h>

/*
** Gets label from first item of elem by taking what comes before LABEL_CHAR.
** Verifies that label if properly formatted with LABEL_CHARS.
** Allocate label struct, fill it with name and offset and assign it
** to new_label. We get the offset by looking at global.
*/
t_error		get_label(t_label **new_label, char **elem)
{
	char	*label_char;
	size_t	len;
	t_label	*new;

	printf(RED"get_label:\n"RESET);
	label_char = ft_strchr(elem[0], LABEL_CHAR);
	if (!label_char)
		return NULL;
	new = malloc(sizeof(t_label));
	if (!new)
		return ft_strdup("could not allocate t_label");
	len = label_char - elem[0];
	new->name = ft_strsub(elem[0], 0, len);
	new->offset = g_offset;
	//printf("new->name = %s / new->offset = %zu\n", new->name, new->offset);
	*new_label = new;
	return NULL;
}

