#include <assembler.h>

/*
** Parses elem to get the instruction string
*/
char		*get_opstr(char **elem)
{
	char	*label_char;
	size_t	len;

	label_char = ft_strchr(elem[0], LABEL_CHAR);
	if (label_char)
	{
		if (*(label_char + 1))
		{
			len = ft_strlen(label_char + 1);
			return ft_strsub(elem[0], label_char + 1 - elem[0], len);
		}
		if (!elem[1])
			return NULL;
		return elem[1];
	}
	return elem[0];
}

/*
** Gets the opcode from elem by looking at first elem, to check if op string is
** contained after LABEL_CHAR, if not, then by looking at second elem.
** Once we have op string, we check op array to see if the string is
** valid and to get the corresponding opcode and assign to dst.
*/
t_error		get_opcode(t_instruction *instruction, char **elem)
{
	char	*opstr;
	int	i;

	printf(RED"get_opcode:\n"RESET);
	opstr = get_opstr(elem);
	if (!opstr)
		return NULL;
	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strcmp(g_op_tab[i].name, opstr) == 0)
		{
			instruction->opcode = g_op_tab[i].opcode;
			printf("opcode = %d\n", instruction->opcode);
			return NULL;
		}
		i++;
	}
	return ft_strjoin("invalid operation: ", opstr);
}

/*
** Sets the encoding byte of instruction by looking if this op has one and then
** checking the type of the arguments.
*/
void		set_encoding_byte(t_instruction *instruction)
{
	printf(RED"set_encoding_byte:\n"RESET);
	(void)instruction;
}

/*
** Updates current offset (number of bytes of instructions already parsed) by 
** incrementing with the byte size of instruction. The byte size of instruction
** is: opcode + encoding + sum(arguments size).
*/
void		update_offset(t_instruction *instruction)
{
	printf(RED"update_offset:\n"RESET);
	(void)instruction;
}

/*
** Gets the instruction, if it exists, from the split elements of the line.
** First allocates new instruction struct, then feed it field by field.
*/
t_error		get_instruction(t_instruction **dst, char **elem)
{
	t_instruction	*new;
	t_error		err;

	printf(RED"get_instruction:\n"RESET);
	// if len(elem) is <= 1 or elem[1] is a comment, set dst = NULL;
	new = malloc(sizeof(t_instruction));
	if (!new)
		return ft_strdup("could not allocate memory");
	*dst = new;
	err = get_opcode(new, elem);
	if (err)
		return err;
	err = get_args(new, elem);
	if (err)
		return err;
	set_encoding_byte(new);
	update_offset(new);
	return NULL;
}
