/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:31:59 by qpeng             #+#    #+#             */
/*   Updated: 2019/09/18 12:58:49 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vm.h"

int8_t     *g_ownerbase;

static void    save_flag(t_vm *vm, char *filename)
{
	if (!scmp_(filename, "gui") || !scmp_(filename, "v"))
		vm->flag |= FL_GUI;
	else if (!scmp_(filename, "d") || !scmp_(filename, "dump"))
		vm->flag |= FL_DUMP;
	else
		ERROR(RED BOLD"Error: flag invalid.\n"RESET);
}

void           dump_mem(t_vm *vm)
{
	int                 i;
	unsigned            siz;

	i = 0;
	siz = (unsigned)sqrt(MEM_SIZE);
	while (i < MEM_SIZE) // < MEM_SIZE
	{
		if (i % siz == 0)
		{
			if (i)
				printf("\n");
			printf("%#06x : ", i);
		}
		h_puthex(vm->memory[i]);
		printf(" ");
		i++;
	}
	write(1, "\n", 1);
	// printf("\nOWNER MAP: \n");
	// i ^= i;
	// while (i < MEM_SIZE) // < MEM_SIZE
	// {
	// 	if (i % siz == 0)
	// 	{
	// 		if (i)
	// 			printf("\n");
	// 		printf("%#06x : ", i);
	// 	}
	// 	if (vm->owner[i] != 7)
	// 		printf("%02d", vm->owner[i]);
	// 	else
	// 		printf("__");
	// 	printf(" ");
	// 	i++;
	// }
	// printf("\n");
}

void    print_mem(t_vm *vm, t_gui *gui)
{
	if (vm->flag &= FL_GUI)
	{
		int                 i;
		int                 x;
		int                 y;

		i = 0;
		x = -2;
		y = 1;
		int color[4] = {COLOR_YELLOW, COLOR_GREEN, COLOR_RED, COLOR_MAGENTA};
		while (i < MEM_SIZE)
		{
			if (x == MAX_X - 2)
			{
				x = -2;
				++y;
			}
			x += 3;
			if (vm->owner[i] != 7)
			{
				init_pair(vm->owner[i] + 2, color[vm->owner[i] + 1], COLOR_BLACK);
				wattron(gui->win, COLOR_PAIR(vm->owner[i] + 2));
				mvwprintw(gui->win, y, x, "%02x", vm->memory[i]);
				wattroff(gui->win, COLOR_PAIR(vm->owner[i] + 2));
			}
			++i;
		}
	}
}

void    loader(t_vm *vm, char *arg)
{
	int fd;

	if (*arg == '-')
	{
		save_flag(vm, &(arg[1]));
		return ;
	}
	else if (ft_strstr(arg, ".cor"))
	{
		if ((fd = open(arg, O_RDONLY)) == -1)
			PERROR("open"); 
		ch_load_champ(vm, fd);
	}
	else
	{
		if (sverif_(arg, "0123456789") && vm->flag & FL_DUMP)
			vm->corewar.dump_cycle = ft_atoi(arg);
		else
			ERROR(RED BOLD"Error: Invalid element as argument.\n"RESET);
	}
}