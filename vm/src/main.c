/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:01 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/13 17:26:47 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"
#include <stdio.h>
#include <string.h>
uint8_t	*g_base;


void    run(t_vm *vm)
{
    while (1)
    {
        ++vm->corewar.cycle;
        // if (++vm->corewar.cycle > vm->corewar.dump_cycle)
        //     print_mem(vm);
        process_loop(vm);
        // if (vm->corewar.cycle > vm->corewar.kill_cycle)
        //     printf("start killing!\n");
        if (!vm->nprocess)
            ERROR("some one win!");
        // gui shit
        if (vm->corewar.cycle > 1000)
            break ;
    }
}

void    read_args(t_vm *vm, int ac, char **av)
{
    int     i;

    i = 1;
    while (i < ac)
    {
      
        loader(vm, av[i]);
        i++;
    }
}

void    cleanup(t_vm *vm)
{
    t_process *tmp = vm->process_list;
    while (tmp)
    {
        tmp = tmp->next;
        free(tmp);
    }
}

int     main(int ac, char **av)
{
    t_vm vm;
    
    bzero_(&vm, sizeof(t_vm));
    vm.debug_mode = 1;
    vm.corewar.nplayers = ac - 1;
    g_base = vm.memory;
    setbuf(stdout, NULL);
    if (ac < 2)
    {
        printf("usage\n");
        exit(EXIT_SUCCESS);
    }
    read_args(&vm, ac, av);
    run(&vm);
    cleanup(&vm);
    return (0);
}