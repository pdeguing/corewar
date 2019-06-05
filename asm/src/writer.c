#include <assembler.h>
#include <sys/stat.h>

/*
** Verifies that the champ has proper formatting and opens the destination file.
*/
static t_error		open_file(int *fd, t_champ *champ)
{
	char		*file_name;

	if (ft_strlen(champ->name) > PROG_NAME_LENGTH)
		return ft_strdup(RED"Name size is too big"RESET);
	if (ft_strlen(champ->comment) > COMMENT_LENGTH)
		return ft_strdup(RED"Comment size is too big"RESET);
	file_name = ft_strjoin(champ->fname, ".cor");
	*fd = open(file_name, O_WRONLY | O_CREAT);
	if (*fd < 0)
	{
		free(file_name);
		return ft_strdup(RED"File couldn't be created"RESET);
	}
	chmod(file_name, S_IRWXU);
	ft_printf(GREEN"writing output to \x1b[93m%s\n"RESET, file_name);
	free(file_name);
	return NULL;
}

/*
** Prints t_header to .cor file.
*/
static t_error		print_header(t_champ *champ, int fd)
{
	header_t	 header;

	ft_bzero(&header, sizeof(header_t));
	header.magic = swap_endian(COREWAR_EXEC_MAGIC);
	ft_strcpy(header.prog_name, champ->name);
	ft_strcpy(header.comment, champ->comment);
	header.prog_size = swap_endian(g_offset);
	write(fd, &header, sizeof(header_t));
	return NULL;
}

/*
** Prints one instruction to fd.
*/
t_error			print_instruction(t_instruction *ins, int fd)
{
	uint32_t	tmp;
	int			i;

	write(fd, &ins->opcode, 1);
	if (ins->encoding_byte)
		write(fd, &ins->encoding_byte, 1);
	i = 0;
	while (i < ins->n_args)
	{
		if (ins->args[i].size == 4 || ins->args[i].size == 2)
		{
			tmp = swap_endian(ins->args[i].value);
			if (ins->args[i].size == 2)
				tmp >>= 16;
			write(fd, &tmp, ins->args[i].size);
		}
		else
			write(fd, &ins->args[i].value, ins->args[i].size);
		i++;
	}
	return NULL;
}

/*
** Prints list of instructions to fd.
*/
static t_error		print_instructions(t_vector *instructions, int fd)
{
	int		i;
	t_instruction	*ins;

	i = 0;
	while (i < instructions->size)
	{
		ins = (t_instruction *)vector_get(instructions, i);
		if (ins->opcode)
			print_instruction(ins, fd);
		i++;
	}
	return NULL;
}

/*
** Writes header and compiled instructions to .cor file.
*/

t_error		write_file(t_champ *champ, t_vector *instructions)
{
	t_error err;
	int	fd;

	err = NULL;
	fd = 0;
	err = open_file(&fd, champ);
	if (!err)
		err = print_header(champ, fd);
	if (!err)
		err = print_instructions(instructions, fd);
	close(fd);
	return err;
}
