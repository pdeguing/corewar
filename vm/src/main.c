#include <corewar.h>

int	main(int ac, char **av)
{
	t_vm	vm;

	ft_bzero(&vm, sizeof(vm));
	if (parse_args(&vm, ac - 1, av + 1) < 0)
	{
		ft_printf("usage: ./corewar  [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
		return -1;
	}
	return 0;
}
