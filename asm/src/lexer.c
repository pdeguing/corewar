/**
 * File              : lexer.c
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#include <assembler.h>

/*
** Replaces in str every occurence of a by b.
*/
static void	replace(char *str, char a, char b)
{
	while (*str)
	{
		if (*str == a)
			*str = b;
		str++;
	}
}

/*
** Gets label from str by taking what comes before LABEL_CHAR. Verifies that
** label if properly formatted with LABEL_CHARS. Allocate label struct, fill
** it with name and offset and assign it to new_label. We get the offset by
** looking at size of instructions array.
*/
t_error		get_label(t_label **new_label, char *str, t_darray *instructions)
{
	(void)new_label;
	(void)str;
	(void)instructions;
	return NULL;
}

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
** Gets the arguments of the instruction. First checks how many arguments are
** expected for this opcode, then tries to extract them from elem and verifies
** the formating. For each argument, we need to create a corresponding
** t_argument struct, and feed the label reference if appropriate, the type, the
** compiled size by looking at 'thefuck' in t_op struct and assigning its value
** in case it is not a reference.
*/
t_error		get_args(t_instruction *instruction, char **elem)
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
	return NULL;
}

/*
 ** Parses a line into an instruction and possibly a label.
 */
t_error		parse_line(t_darray *instructions, t_darray *labels, char *line)
{
	char		**elem;
	t_label		*new_label;
	t_instruction	*new_instruction;
	t_error		err;

	new_label = NULL;
	new_instruction = NULL;

	replace(line, TAB, WHITE_SPACE);
	replace(line, WHITE_SPACE, SEPARATOR_CHAR);
	elem = ft_strsplit(line, SEPARATOR_CHAR);
	if (!elem)
		return ft_strdup("could not split the line");

	err = get_label(&new_label, elem, instructions);
	if (err)
		return err;
	if (new_label)
		append(labels, new_label);

	err = get_instruction(&new_instruction, elem);
	if (err)
		return err;
	if (new_instruction)
		append(instructions, new_instruction);

	return NULL;
}

/*
** Feeds the label references in instructions' arguments with the according
** label offset. Return an error if the label does not exist.
*/
t_err		feed_references(t_darray *instructions, t_darray labels)
{
	(void)instructions;
	(void)labels;
	return NULL;
}

/*
** Transforms the t_champ struct into a list of instructions, verifies
** that instructions are valid and returns err if they are not.
*/
t_error		lexer(t_darray *instructions, t_champ *champ)
{
	char		**lines;
	int		i;
	t_darray	labels;
	t_error		err;

	lines = ft_strsplit(champ->content);
	if (!lines)
		return ft_strdup("Could not split into array of lines");
	i = 0;
	while (lines[i])
	{
		parse_line(instructions, labels, lines[i]);
		i++;

	}
	err = feed_references(instructions, labels);
	if (err)
		return err;
	// free(labels); we don't need the label array anymore once we have instructions
	return NULL;
	// split champ->content into array of lines
	// for each line, split by space:
	//
	// 			if label:
	// 				append label to label_array,
	// 					with offset = total_instruction_size before label
	// 			if instructions:
	// 				create instruction struct
	// 				determine instruction size
	// 				add instruction size to total_instruction_size
	// 				append instruction to instruction_array
	// 					check format
	// 			if #:
	// 				ignore rest
	// 			else if anything else
	// 				format error
	//
	return NULL;
}
