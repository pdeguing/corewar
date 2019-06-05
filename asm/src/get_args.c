#include <assembler.h>
#include "../include/assembler.h"
#include "../include/op.h"
#include "../../libft/includes/libft.h"

/*
** Extensive function of fill_args, gets the value of the parameters.
*/

static t_error		get_value(t_instruction *inst, char *elem, int n)
{
	int		i;

	i = 0;
	inst->args[n].label = NULL;
	if (inst->args[n].type == REG_CODE)
		inst->args[n].value = ft_atoi(ft_strsub(elem, 1, ft_strlen(elem)));
	else if (inst->args[n].type == DIR_CODE)
	{
		if (elem[1] == ':')
		{
			inst->args[n].label = ft_strsub(elem, 2, ft_strlen(elem));
			inst->args[n].value = 0;
		}
		else if (ft_isdigit(elem[1]) || elem[1] == '-')
			inst->args[n].value = ft_atoi(ft_strsub(elem, 1, ft_strlen(elem)));
	}
	else if (inst->args[n].type == IND_CODE)
	{
		inst->args[n].value = ft_atoi(ft_strsub(elem, 0, ft_strlen(elem)));
	}
	return (NULL);
}

/*
** Extensive function of fill_args, gets the type and size of the parameters.
*/

static t_error		get_type(t_instruction *inst, char *elem, int count, int n)
{
		if (!elem)
			return (ft_strdup(RED"Invalid parameter"RESET));
		if (elem[0] == 'r')
		{
			inst->args[count].type = REG_CODE;
			inst->args[count].size = 1;
		}
		else if (elem[0] == '%')
			inst->args[count].type = DIR_CODE;
		else if (ft_isdigit(elem[0]) || (elem[0] == '-' &&
					ft_isdigit(elem[1])))
			inst->args[count].type = IND_CODE;
		if (inst->args[count].type == IND_CODE || (inst->args[count].type ==
					DIR_CODE && g_op_tab[n].thefuck == 1))
			inst->args[count].size = 2;
		else if (inst->args[count].type == DIR_CODE && g_op_tab[n].thefuck == 0)
			inst->args[count].size = 4;
		return (NULL);
}

/*
** Fill inst strcuture for this line, get the size, value and type of
** the parameters before writing them into the '.s' file.
*/

static t_error		fill_arg(t_instruction *inst, char **elem, int current, int n)
{
	t_error	err;
	int		count;
	int		tmp;

	err = NULL;
	count = 0;
	tmp = current;
	while (current < (tmp + g_op_tab[n].n_param))
	{
		err = get_type(inst, elem[current], count, n);
		if (err)
			return (err);
		err = get_value(inst, elem[current], count);
		if (err)
			return (err);
		current++;
		count++;
	}
	if (count != g_op_tab[n].n_param)
		return (ft_strdup(RED"Number of parameters invalid"RESET));
	return (NULL);
}

/*
** Dispatches the labels name and sends its id (1 - 17) to fill_arg.
*/

static t_error		dispatch_arg(t_instruction *inst, char **elem, int current)
{
	t_error		err;
	int			i;

	i = -1;
	err = NULL;
	while (++i < 16)
	{
		if (!ft_strcmp(elem[current], g_op_tab[i].name))
		{
			inst->n_args = g_op_tab[i].n_param;
			err = fill_arg(inst, elem, ++current, i);
			if (err)
				return (err);
			break ;
		}
	}
	return (NULL);
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
	t_error	err;
	int		i;

	err = NULL;
	i = -1;
	while (elem[1] && elem[++i])
	{
		if (elem[i + 1] && i == 0 && elem[i][ft_strlen(elem[i]) - 1] == ':')
			i++;
		if (elem[i])
		{
			err = dispatch_arg(instruction, elem, i);
			if (err)
				return (err);
			break ;
		}
	}
	return (NULL);
}
