/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 02:39:18 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/13 17:27:26 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_instr_hdlr instr_funptr[] = {
    ft_live,
    ft_ld,
    ft_st,
    ft_add,
    ft_sub,
    ft_and, 
    ft_or,
    ft_xor,
    ft_zjmp,
    ft_ldi,
    ft_sti,
    ft_fork,
    ft_lld,
    ft_lldi,
    ft_lfork,
    ft_aff
};

void    fork_process(t_vm *vm, t_process *parent, int32_t offset, t_bool far)
{
    t_process           *process;

    process = malloc(sizeof(t_process));
    bzero_(process, sizeof(t_process));
    memcpy_(process->registers, parent->registers, sizeof(process->registers));
    process->pc =  parent->pc + (far ? offset : (offset % IDX_MOD));
    process->pid = parent->pid;
    process->champion = parent->champion;
    if (vm->process_list)
        process->next = vm->process_list;
    vm->process_list = process;
    vm->nprocess++;
}

t_byte  *advance_pc(t_byte **cur, int32_t offset)
{
    t_byte          *end;
    off_t           diff;

    end = g_base + MEM_SIZE;
    if ((diff = ((*cur += offset) - end)) > 0)
        *cur = g_base + diff;
    //printf("jmp[%d] to: %p %x\n", offset, *cur, **cur);
    return (*cur);
}

void    execute(t_vm *vm, t_instr *cinstr)
{
    (instr_funptr[cinstr->instr - 1])(vm, cinstr);
    //printf("Running... %s\n", g_op_tab[instr - 1].name);
}

/*
** advance the program counter to the next instruction
** and decode it into argvt and argv
** pc = program counter / instruction pointer
** acb = argument's coding byte
*/

// void    decode_without_acb(t_byte **pc, t_arg *arg,  t_op *op)
// {
//     t_byte         acb;
//     uint8_t        i;

//     i = ITERATOR;
//     advance_pc(pc, 1);
//     arg[0].argv = *pc;
//     advance_pc(pc, 4);
//     return ;
//     // while (INC(i) < op->argc)
//     // {
//     //     arg[i].argv = *pc;
//     //     advance_pc(pc, 4);
//     //     if (op->argvt[i] & T_DIR)
//     //         advance_pc(pc, DIR_SIZE);
//     //     else if (op->argvt[i] & T_REG)
//     //         advance_pc(pc, REG_SIZE);
//     //     else if (op->argvt[i] & T_IND)
//     //         advance_pc(pc, IND_SIZE);
//     // }
// }

void    decode_with_acb(t_byte **pc, t_arg *arg, t_op *op)
{
    t_byte         acb;
    uint8_t        i;

    i = ITERATOR;
    acb = *(advance_pc(pc, 1));             //printf("%x\n", acb);
    advance_pc(pc, 1);  
    while (INC(i) < op->argc)
    {
        arg[i].argv = *pc;
        arg[i].argvt = GET_ACB_TYPE(acb);
        if (arg[i].argvt == REGISTER_TYPE)
            advance_pc(pc, 1);
		else if (arg[i].argvt == DIRECT_TYPE)
		{
            if (op->truncate)
                advance_pc(pc, DIR_SIZE >> 1);
            else 
                advance_pc(pc, DIR_SIZE);
        }
		else
            advance_pc(pc, IND_SIZE);
        acb <<= 2;
    }
}

void    debug_loop()
{
    
}

void    instruction_cycle(t_vm *vm, t_process *cp)
{
    t_op                *op;
    static t_instr      i;
    
    i.instr = *cp->pc;

    cp->cpc = i.pc = cp->pc;
    op = &INSTR[i.instr - 1];
    i.argc = op->argc;
    if (op->coding_byte)
        decode_with_acb(&cp->pc, i.arg, op);
    else
    {
        advance_pc(&cp->pc, 1);
        i.arg[0].argv = cp->pc;
        advance_pc(&cp->pc, 4);
    }
    g_cur_process = cp;
    execute(vm, &i);
    print_mem(vm);
}

void    print_register(t_process *cp)
{
    int     i;

    i = 0;
    printf("register status: [");
    while (i < REG_NUMBER)
    {
        printf(" %d | ", cp->registers[i]);
        i++;
    }
    printf("]\n");
}

void    process_loop(t_vm   *vm)
{
    t_process       *cp;
    static uint32_t r_cycles[MAX_PLAYERS + 1];
    
    cp = vm->process_list;
    while (cp)
    {
        //printf("current cycle: %d l: %d, %d\n", vm->corewar.cycle, r_cycles[cp->pid + 1], *(cp->pc));
        if (*(cp->pc) && *(cp->pc) <= 16)
        {
            if (!r_cycles[cp->pid + 1])
                r_cycles[cp->pid + 1] = INSTR[*(cp->pc) - 1].cycles;
            r_cycles[cp->pid + 1]--;
            if (!r_cycles[cp->pid + 1])
            {
                printf("Pid: %d\n", cp->pid);
                printf("Cycle: %d\n", vm->corewar.cycle);
                if (vm->debug_mode)
                    print_register(cp);
                instruction_cycle(vm, cp);
                 if (vm->debug_mode)
                    print_register(cp);
                printf("%p %x\n", cp->pc, *(cp->pc));
                printf("---------------\n");
                r_cycles[cp->pid + 1] ^= r_cycles[cp->pid + 1];
            }
        }
        cp = cp->next;
    }
}
// .name "zork"
// .comment "just a basic living prog"
		
// l2:	sti	r1,%:live,%0
// 	and	r1,%0,r1
// live:	live	%1
// 	zjmp	%:live