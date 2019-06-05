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
			return (ft_strsub(elem[0], label_char + 1 - elem[0], len));
		}
		if (!elem[1])
			return (NULL);
		return (ft_strdup(elem[1]));
	}
	return (ft_strdup(elem[0]));
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
	int		i;

	opstr = get_opstr(elem);
	if (!opstr)
		return (NULL);
	i = 0;
	while (g_op_tab[i].name)
	{
		if (!ft_strcmp(g_op_tab[i].name, opstr))
		{
			instruction->opcode = g_op_tab[i].opcode;
			free(opstr);
			return (NULL);
		}
		i++;
	}
	return (ft_strjoinfree2(RED"invalid operation: "RESET, opstr));
}

/*
** Sets the encoding byte of instruction by looking if this op has one and then
** checking the type of the arguments.
*/

void		set_encoding_byte(t_instruction *instruction)
{
	uint32_t	args[3];
	int		i;

	args[0] = 0;
	args[1] = 0;
	args[2] = 0;
	if (instruction->opcode <= 0 || !g_op_tab[instruction->opcode - 1].what)
		return ;
	instruction->encoding_byte = 0;
	i = 0;
	while (i < instruction->n_args)
	{
		if (instruction->args[i].type == T_REG)
			args[i] = REG_CODE;
		else if (instruction->args[i].type == T_DIR)
			args[i] = DIR_CODE;
		else
			args[i] = IND_CODE;
		i++;
	}
	instruction->encoding_byte += args[0] << 6;
	instruction->encoding_byte += args[1] << 4;
	instruction->encoding_byte += args[2] << 2;
}

/*
** Calculate byte size of instruction. The byte size of instruction
** is: opcode + encoding + sum(arguments size).
*/

void		set_size(t_instruction *instruction)
{
	int	i;

	instruction->size = 0;
	if (!instruction->opcode)
		return ;
	instruction->size++; 
	if (instruction->encoding_byte)
		instruction->size++;
	i = 0;
	while (i < instruction->n_args)
	{
		instruction->size += instruction->args[i].size;
		i++;
	}
}

/*
** Gets the instruction, if it exists, from the split elements of the line.
** First allocates new instruction struct, then feed it field by field.
*/

t_error		get_instruction(t_instruction **dst, char **elem)
{
	t_instruction	*new;
	t_error		err;

	err = NULL;
	new = malloc(sizeof(t_instruction));
	if (!new)
		return (ft_strdup("could not allocate memory"));
	ft_bzero(new, sizeof(t_instruction));
	*dst = new;
	err = get_opcode(new, elem);
	if (err)
		return (err);
	err = get_args(new, elem);
	if (err)
		return (err);
	set_encoding_byte(new);
	set_size(new);
	new->offset = g_offset;
	g_offset += new->size;
	return (NULL);
}
