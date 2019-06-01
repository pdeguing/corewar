/**
 * File              : assembler.h
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#ifndef	 ASSEMBLER_H
# define ASSEMBLER_H

# include "../../libft/includes/libft.h"
# include "op.h"
# include "vector.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# define RED	"\x1b[91m"
# define RESET	"\x1b[0m"

# define WHITE_SPACE		32
# define TAB			9
# define NEWLINE		10

typedef char*			t_error;

typedef struct			s_champ
{
	char			*name;
	char			*comment;
	char			*content;
}				t_champ;

/*
** Stores arguments form instructions:
** 	-> label = if not NULL, argument is a reference and should be filled\
					later on;
** 	-> type = (0, 1, 2) (register, direct, indirect);
** 	-> size = (1, 2, 4) (register, indirect OR direct with thefuck == 1,\
**						direct with thefuck == 0);
**	-> value = compiled value;
*/
typedef struct			s_argument
{
	char			*label;
	int			type;
	int			compiled_size;
	int			value;

}				t_argument;

typedef struct			s_instruction
{
	int			opcode;
	uint32_t		encoding_byte;
	char			*args[3];
}				t_instruction;

typedef struct			s_label
{
	char			*name;
	size_t			offset;
}				t_label;

size_t				g_offset;

t_error		assembler(char *filename);
void		initChamp(t_champ *champ);
t_error		lexer(t_vector *instructions, t_champ *champ);
t_error		verifyFilename(char *filename);
t_error		fillChamp(t_champ *champ, int fd);
t_error		parser(t_champ *champ, char *filename);
t_error		write_file(t_champ *champ, t_vector *instructions);
t_error		getName(char **dst, int fd);
t_error		getComment(char **dst, int fd);
t_error		getContent(char **dst, int fd);

t_error		get_label(t_label **new_label, char **elem);

t_error		get_opcode(t_instruction *instruction, char **elem);
void		set_encoding_byte(t_instruction *instruction);
void		update_offset(t_instruction *instruction);
t_error		get_args(t_instruction *instruction, char **elem);
t_error		get_instruction(t_instruction **dst, char **elem);

#endif
