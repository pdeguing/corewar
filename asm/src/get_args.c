#include <assembler.h>

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

