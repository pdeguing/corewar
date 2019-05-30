/*
** Prints t_header to .cor file.
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
	return NULL;
}

/*
** Prints list of instructions to .cor file.
*/
static t_error		print_instructions(t_instruction *instructions)
{
	(void)instructions;
	return NULL;
}

/*
** Writes header and compiled instructions to .cor file.
*/
t_error		write_file(t_champ *champ, t_instruction *instructions)
{
	t_error err;

	err = print_header(champ);
	if (err)
		return (err);
	err = print_instructions(instructions);
	if (err)
		return err;
	return NULL;
}
