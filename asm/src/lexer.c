/**
 * File              : lexer.c
 * Author            : pdeguing <pdeguing@student.42.us.org>
 * Date              : 25.05.2019
 * Last Modified Date: 25.05.2019
 * Last Modified By  : pdeguing <pdeguing@student.42.us.org>
 */

#include <assembler.h>

static int				is_in(char *str, t_label **label, t_info *info)
{
	int		i;

	i = -1;
	while (++i < info->index)
	{
		//ft_printf("str is %s\tlabel is %s\n", str, label[info->index]->name);
		if (label[i] && ft_strequ(label[i]->name, str))
			return (1);
	}
	return (0);
}

/*
** Retrieves the label's name and it's offset position and check that it
** doesn't already exists.
*/

static t_error			get_label(t_info *info, t_label **label, char *line)
{
	int		max;
	char	*tmp;

	(void)label;
	max = 0;
	while (line[max] && line[max] != ' ' && line[max] != '\t')
		max++;
	tmp = ft_strsub(line, 0, max);
	if (tmp[max - 1] != ':')
		return ft_strdup(RED"Label not well formated"RESET);
	if (!is_in(tmp, label, info))
	{
		append(t_darray, t_label)
		ft_printf("index is %d\n", info->index);
		label[info->index]->name = ft_strdup(tmp);
		ft_putstr(label[info->index]->name);
		ft_putchar('\n');
		info->index++;
	}
	return NULL;
}

/*
** Retrieves all the informations on that line (label, instructions).
*/

static t_error			get_info(t_info *info, char *line, t_label **label, \
		t_instruction **inst)
{
	int		i;

	i = 0;
	if (line[i] != ' ' && line[i] != '\t')
		get_label(info, label, line);
	return NULL;
}

/*
** Transforms the t_champ struct into a list of instructions, verifies
** that instructions are valid and returns err if they are not.
*/

t_error					lexer(t_darray *labels, t_instruction **instructions,\
		t_champ *champ)
{
	int		i;
	char	**lines;
	t_info	*info;

	i = -1;
	info = malloc(sizeof(info));
	info->index = 0;
	lines = ft_strsplit(champ->content, '\n');
	while (lines[++i])
	{
		//ft_putstr(lines[i]);
		//ft_putchar('\n');
		get_info(info, lines[i], label, instructions);
			//return ft_strdup(RED"Couldn't get information"RESET);
	}
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
