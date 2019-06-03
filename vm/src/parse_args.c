#include <corewar.h>

/*
** Parses command-line arguments and feed dump cycles and vector of champs.
*/
int	parse_args(t_vm *vm, int n_args, char **args)
{
	int	i;

	if (n_args < 1)
		return -1;
	i = 0;
	while (i < n_args)
	{
		if (!ft_strcmp(args[i], "-dump"))
		{
			i++;
			if (i >= n_args || !ft_isdigit(*args[i]))
				return -1;
			vm->dump = ft_atoi(args[i]);
		}
		else
		{
			if (!ft_strcmp(args[i], "-n"))
			{
				i++;
				if (i >= n_args || !ft_isdigit(*args[i]))
					return -1;
				// get champion number
				// get champion program
			}
		}
		i++;
	}
}
