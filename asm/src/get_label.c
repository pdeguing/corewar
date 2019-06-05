#include <assembler.h>

/*
** Checks if the label is properly formated with only LABEL_CHARS.
*/
static int	is_invalid_label(char *label)
{
	while (*label)
	{
		if (!ft_strchr(LABEL_CHARS, *label))
			return (1);
		label++;
	}
	return (0);
}

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
	char	*name;

	label_char = ft_strchr(elem[0], LABEL_CHAR);
	if (!label_char)
		return (NULL);
	len = label_char - elem[0];
	name = ft_strsub(elem[0], 0, len);
	if (is_invalid_label(name))
	{
		free(name);
		return (ft_strjoinfree2(RED"label name is invalid: "RESET, name));
	}
	new = malloc(sizeof(t_label));
	if (!new)
		return (ft_strdup(RED"could not allocate t_label"RESET));
	new->name = name;
	new->offset = g_offset;
	*new_label = new;
	return (NULL);
}
