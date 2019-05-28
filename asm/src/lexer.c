/**
 * File              : lexer.c
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#include <assembler.h>

/*
** Transforms the t_champ struct into a list of instructions, verifies
** that instructions are valid and returns err if they are not.
*/
t_error		lexer(t_champ *champ)
{
	if (champ == NULL)
		printf("NULL\n");
	printf("name = %s\n", champ->name);
	printf("comment = %s\n", champ->comment);
	printf("content = %s\n", champ->content);
	return NULL;
}
