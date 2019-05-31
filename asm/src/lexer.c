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
** label if properly formatted with LABEL_CHARS.
*/
t_error		get_label(t_label **new_label, char *str)
{
	if (ft_strchr(elem[0], LABEL_CHAR)) 
	{
		if (err)
			return err;
		// op = sub what is after :
	}
}

/*
** Gets the instruction, if it exists, from the split elements of the line.
*/
t_error		get_instruction(t_instruction **new_instruction, char **elem)
{
	t_error		err;

	err = get_opcode(&current->opcode, elem);
	if (err)
		return err;
	// if op is NULL get op, else we got it before
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

	err = get_label(&new_label, elem);
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
	// free(labels);
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
