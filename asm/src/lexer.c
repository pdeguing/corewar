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
** Prints t_header in the file .cor
*/

static t_error		print_header(t_champ *champ)
{
	int			fd;
	char		*file_name;
	header_t	 header;

	if (ft_strlen(champ->name) > PROG_NAME_LENGTH)
		return ft_strdup(RED"Name size is too big"RESET);
	if (ft_strlen(champ->comment) > COMMENT_LENGTH)
		return ft_strdup(RED"Comment size is too big"RESET);
	header.magic = COREWAR_EXEC_MAGIC;
	ft_bzero(header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(header.prog_name, COMMENT_LENGTH + 1);
	ft_strcpy(header.prog_name, champ->name);
	ft_strcpy(header.comment, champ->comment);
	header.prog_size = 0;
	file_name = ft_strjoin(header.prog_name, ".cor");
	if ((fd = open(file_name, O_WRONLY | O_CREAT)) < 0)
		return ft_strdup(RED"File couldn't be created"RESET);
	write(fd, &header, sizeof(header_t));
	return (NULL);
}

/*
** Transforms the t_champ struct into a list of instructions, verifies
** that instructions are valid and returns err if they are not.
*/
t_error		lexer(t_champ *champ)
{
	t_error err;

	if (champ == NULL)
		printf("NULL\n");
	err = print_header(champ);
	if (err)
		return (err);
	/*
	printf("name = %s\n", champ->name);
	printf("comment = %s\n", champ->comment);
	printf("content = %s\n", champ->content);
	*/
	return NULL;
}
