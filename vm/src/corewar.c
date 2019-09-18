/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:01 by qpeng             #+#    #+#             */
/*   Updated: 2019/09/18 12:53:51 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "vm.h"

t_byte	*g_base;

/*
** Removes a process from the list of processes in t_process struct.
** @param {t_vm} vm - vm struct
*/

static void			process_kill(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
}

/*
** Checks if each process has indeed made a live call during it's turn.
** if not, calls the "process_kill" function.
** @param {t_vm} vm - vm struct
*/

static void			process_check(t_vm *vm)
{
	int 	i;

	i = -1;
	while (++i < vm->nprocess)
	{
		if (vm->corewar.call_live == 0) //THIS IS WRONG, NEEDS TO CHECK IF EACH PROCESS CALLED A LIVE
			process_kill(vm, i);
	}
}

/*
** Check for cycle_to die and decrements it if needed.
** @param {t_vm} vm - vm struct 
*/

static int			cycle_check(t_vm *vm)
{
	if ((vm->corewar.cycle % vm->corewar.kill_cycle) == 0)
	{
		vm->corewar.kill_turn++;
		if (vm->corewar.call_live >= NBR_LIVE || vm->corewar.kill_turn > MAX_CHECKS)
		{
			vm->corewar.kill_cycle -= CYCLE_DELTA;
			vm->corewar.kill_turn = 0;
		}
		process_check(vm);
		vm->corewar.call_live = 0;
	}
	if (vm->corewar.cycle == (uint32_t)vm->corewar.dump_cycle)
	{
		dump_mem(vm);
	}
	return (0);
}

/*
**  run corewar game && initialize GUI if flag (-v | -gui) enabled.
**  @param {t_vm} vm - vm struct 
*/

void    cw_run(t_vm *vm)
{
	t_gui       gui;

	gui.speed = 1;
	if (vm->flag &= FL_GUI)
		init_gui(&gui);
	while (1)
	{
		if (vm->flag & FL_GUI)
			update_gui(vm, &gui);
		vm->corewar.cycle += gui.speed * 2;
		p_process_loop(vm);
		cycle_check(vm);
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

/*
**  clean up stage
**  deallocates all the resouces back
** 
**  @param {t_vm} vm - vm struct 
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

/*
**  init all the env
**  set g_base as the beginning of memory 
** 
**  @param {t_vm} vm - vm struct 
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
	vm->corewar.kill_cycle = CYCLE_TO_DIE;
	vm->corewar.call_live = 0;
	memset_(OWNER_START, 7, MEM_SIZE);
	setbuf(stdout, NULL);
}

/*
**  start the corewar game, set up (initialize all the envs)
**  read all the args and run processes
** 
**  @param {int} ac - number of arguments
**  @param {char **} av - argument vector
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