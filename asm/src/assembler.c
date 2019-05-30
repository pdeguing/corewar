/**
 * File              : assembler.c
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#include "assembler.h"

/*
** Sets all members of t_champ struct to NULL.
*/
void		initChamp(t_champ *champ)
{
	champ->name = NULL;
	champ->comment = NULL;
	champ->content = NULL;
}

/*
** Translates assembly source file into a binary file for Corewar virtual
** machine.
*/
t_error		assembler(char *filename)
{
	t_error	err;
	t_champ	champ;
	t_instruction	*instructions;

	initChamp(&champ);
	err = parser(&champ, filename);
	if (err)
		return err;
	err = lexer(&instructions, &champ);
	if (err)
		return err;
	err = write_file(&champ, &instructions);
	if (err)
		return err;
	return NULL;
}
