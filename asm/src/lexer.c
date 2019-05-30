/**
 * File              : lexer.c
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#include <assembler.h>
# define RED "\x1b[91m"
# define RESET "\x1b[0m"

/*
** Transforms the t_champ struct into a list of instructions, verifies
** that instructions are valid and returns err if they are not.
*/
t_error		lexer(t_instruction **instructions, t_champ *champ)
{
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
