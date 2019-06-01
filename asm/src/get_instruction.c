#include <assembler.h>

/*
** Gets the opcode from elem by looking at first elem, to check if op string is
** contained after LABEL_CHAR, if not, then by looking at second elem.
** Once we have op string, we check op array to see if the string is
** valid and to get the corresponding opcode and assign to dst.
*/
t_error		get_opcode(t_instruction *instruction, char **elem)
{
	(void)instruction;
	(void)elem;
	return NULL;
}

/*
** Sets the encoding byte of instruction by looking if this op has one and then
** checking the type of the arguments.
*/
void		set_encoding_byte(t_instruction *instruction)
{
	(void)instruction;
}

/*
** Updates current offset (number of bytes of instructions already parsed) by 
** incrementing with the byte size of instruction. The byte size of instruction
** is: opcode + encoding + sum(arguments size).
*/
void		update_offset(t_instruction *instruction)
{
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
