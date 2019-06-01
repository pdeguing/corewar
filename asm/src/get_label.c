#include <assembler.h>

/*
** Gets label from first item of elem by taking what comes before LABEL_CHAR.
** Verifies that label if properly formatted with LABEL_CHARS.
** Allocate label struct, fill it with name and offset and assign it
** to new_label. We get the offset by looking at global.
*/
t_error		get_label(t_label **new_label, char **elem)
{
	(void)new_label;
	(void)elem;
	(void)g_offset;
	return NULL;
}

