/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:01 by qpeng             #+#    #+#             */
/*   Updated: 2019/09/13 11:28:17 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "vm.h"

t_byte	*g_base;

static int			is_endgame(t_vm *vm)
{
	(void)vm;
	return (0);
}

/**
 *  run corewar game && initialize GUI if flag (-n) enabled.
 *  @param {t_vm} vm - vm struct 
*/

void    cw_run(t_vm *vm)
{
	t_gui       gui;

	if (vm->flag &= FL_GUI)
		init_gui(&gui);
	while (1)
	{
		if (vm->flag & FL_GUI)
		{
			if (update_screen(gui.win, gui.speed) == ESC || update_screen(gui.win_info, gui.speed) == ESC || (vm->corewar.cycle > 1000))
				end_screen();
			if (update_screen(gui.win, gui.speed) == SPACE || update_screen(gui.win_info, gui.speed) == SPACE)
				gui.speed = (gui.speed == 5) ? 1 : gui.speed + 1;
			print_info(&gui, vm);
		}
		vm->corewar.cycle += gui.speed * 2;
		print_mem(vm, &gui);
		p_process_loop(vm);
		if (is_endgame(vm))
			//printf("start killing!\n");
		if (!vm->nprocess)
			ERROR("some one win!");
	}
	if (vm->flag & FL_GUI)
		end_screen();
}

/*
**  read flags and if it's champion file 
**  run loader to load it into corewar
** 
**  @param {t_vm} vm - vm struct 
**  @param {int} ac - number of arguments
**  @param {char **} av - argument vector
*/
void    cw_read_args(t_vm *vm, int ac, char **av)
{
	int     i;

	i = 1;
	while (i < ac)
	{
		loader(vm, av[i]);
		i++;
	}
	if (vm->flag & FL_DUMP && vm->corewar.dump_cycle == -1)
		ERROR(RED BOLD"Error: no dump cycle has been given as arg.\n"RESET);
}

/**
 *  clean up stage
 *  deallocates all the resouces back
 * 
 *  @param {t_vm} vm - vm struct 
 */
void    cw_cleanup(t_vm *vm)
{
	(void)vm;
	// t_process *tmp;
	
	// tmp = vm->process_list;
	// while (tmp)
	// {
	//     tmp = tmp->next;
	//     free(tmp);
	// }
}

/**
 *  init all the env
 *  set g_base as the beginning of memory 
 * 
 *  @param {t_vm} vm - vm struct 
 */
void    cw_env_init(t_vm *vm, int nplayers)
{
	bzero_(vm, sizeof(t_vm));
	vm->debug_mode = 1;
	vm->corewar.nplayers = nplayers;
	g_base = vm->memory;
	vm->corewar.dump_cycle = -1;
	MAP_START = vm->memory;
	OWNER_START = vm->owner;
	memset_(OWNER_START, 7, MEM_SIZE);
	setbuf(stdout, NULL);
}

/**
 *  start the corewar game, set up (initialize all the envs)
 *  read all the args and run processes
 * 
 *  @param {int} ac - number of arguments
 *  @param {char **} av - argument vector
 */
void    cw_start(int ac, char **av)
{
	t_vm vm;
	
	if (ac < 2)
	{
		printf("usage: ./vm <champ1, ...>\n");
		exit(EXIT_SUCCESS);
	}
	cw_env_init(&vm, ac - 1);
	cw_read_args(&vm, ac, av);
	cw_run(&vm);
	cw_cleanup(&vm);
}