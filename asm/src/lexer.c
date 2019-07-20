/**
 * File              : lexer.c
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#include <assembler.h>

size_t				g_offset = 0;

/*
** Swaps memory from BIG-ENDIAN to LITTLE-ENDIAN (or opposite).
*/

uint32_t			swap_endian(uint32_t num)
{
	return ((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) &\
			0xff00) | ((num << 24) & 0xff000000);
}

/*
** Replaces in str every occurence of a by b.
*/

static void			replace(char *str, char a, char b)
{
	while (*str)
	{
		if (*str == a)
			*str = b;
		str++;
	}
}

/*
** Parses a line into an instruction and possibly a label.
*/

t_error				parse_line(t_vector *instructions,
		t_vector *labels, char *line)
{
	char			**elem;
	t_label			*new_label;
	t_instruction	*new_instruction;
	t_error			err;

	err = NULL;
	new_label = NULL;
	new_instruction = NULL;
	replace(line, TAB, WHITE_SPACE);
	replace(line, WHITE_SPACE, SEPARATOR_CHAR);
	elem = ft_strsplit(line, SEPARATOR_CHAR);
	if (!elem || !elem[0] || *elem[0] == '#')
	{
		free_double(elem);
		return (NULL);
	}
	err = get_label(&new_label, elem);
	if (new_label)
		VECTOR_ADD(labels, new_label);
	if (!err)
		err = get_instruction(&new_instruction, elem);
	if (new_instruction)
		VECTOR_ADD(instructions, new_instruction);
	free_double(elem);
	if (err)
		return (err);
	return (NULL);
}

/*
** Frees a double char pointer
*/
void				free_double(char **dptr)
{
	char		**tmp;

	tmp = dptr;
	while (*dptr)
	{
		free(*dptr);
		dptr++;
	}
	free(tmp);
}

/*
** Transforms the t_champ struct into a list of instructions, verifies
** that instructions are valid and returns err if they are not.
*/

t_error				lexer(t_vector *instructions, t_champ *champ)
{
	char		**lines;
	int			i;
	t_vector	labels;
	t_error		err;

	err = NULL;
	VECTOR_INIT(&labels);
	lines = ft_strsplit(champ->content, NEWLINE);
	if (!lines)
		return (ft_strdup(RED"could not split into array of lines"RESET));
	i = 0;
	while (lines[i] && !err)
	{
		if (*lines[i] != COMMENT_CHAR)
			err = parse_line(instructions, &labels, lines[i]);
		i++;
	}
	if (!err)
		err = feed_references(instructions, &labels);
	free_double(lines);
	VECTOR_FREE(&labels);
	if (err)
		return (err);
	return (NULL);
}
