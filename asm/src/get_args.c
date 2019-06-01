#include <assembler.h>

static t_error		get_value(t_instruction *inst, char *elem, int n)
{
	int		i;

	i = 0;
	inst->args[n].label = NULL;
	if (inst->args[n].type == REG_CODE)
		inst->args[n].value = ft_atoi(ft_strsub(elem, 1, ft_strlen(elem) - 1));
	else if (inst->args[n].type == DIR_CODE)
	{
		if (elem[1] == ':')
		{
			inst->args[n].label = ft_strsub(elem, 2, ft_strlen(elem) - 1);
			inst->args[n].value = 0;
		}
		else if (ft_isdigit(elem[1]))
			inst->args[n].value = ft_atoi(ft_strsub(elem, 1, ft_strlen(elem) - 1));
	}
	else if (inst->args[n].type == IND_CODE)
		inst->args[n].value = ft_atoi(ft_strsub(elem, 0, ft_strlen(elem) - 1));
	return NULL;
}

static t_error		fill_arg(t_instruction *inst, char **elem, int current, int n)
{
	int		count;
	int		tmp;

	count = 0;
	tmp = current;
	while (current < (tmp + g_op_tab[n].n_param))
	{
		if (elem[current][0] == 'r')
		{
			inst->args[count].type = REG_CODE;
			inst->args[count].size = 1;
		}
		else if (elem[current][0] == '%')
			inst->args[count].type = DIR_CODE;
		else if (ft_isdigit(elem[current][0]))
			inst->args[count].type = IND_CODE;
		if (inst->args[count].type == IND_CODE || (inst->args[count].type == DIR_CODE && \
					g_op_tab[n].thefuck == 1))
			inst->args[count].size = 2;
		else if (inst->args[count].type == DIR_CODE && g_op_tab[n].thefuck == 0)
			inst->args[count].size = 4;
		get_value(inst, elem[current], count);
		printf(GREEN"LABEL = %s\tTYPE = %d\tSIZE = %zu\tVALUE = %d\n\n"RESET, inst->args[count].label, inst->args[count].type, inst->args[count].size, inst->args[count].value);
		current++;
		count++;
	}
	if (count != g_op_tab[n].n_param)
		return ft_strdup(RED"Number of parameters invalid"RESET);
	return NULL;

}

static t_error		dispatch_arg(t_instruction *inst, char **elem, int current)
{
	int		i;

	i = -1;

	while (++i < 16)
	{
		if (!ft_strcmp(elem[current], g_op_tab[i].name))
		{
			fill_arg(inst, elem, ++current, i);
			break ;
		}
	}
	return NULL;
}


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
	int		i;

	i = -1;
	while (elem[1] && elem[++i])
	{
		if (elem[i + 1] && i == 0 && elem[i][ft_strlen(elem[i]) - 1] == ':')
			i++;
		if (elem[i])
			dispatch_arg(instruction, elem, i);
		//printf(GREEN"%s\n"RESET, elem[i]);
	}
	return NULL;
}
