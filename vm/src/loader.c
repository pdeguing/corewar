/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:31:59 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/13 16:39:50 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <math.h>


/**
 *  parse the champion header into t_hdr
 *  the magic is in little endianess format
 * 
 * @param {t_hdr} hdr - current vm structure
 * @param {int} fd - file descriptor of the file where the
 *      champion is stored
 * 
 */

void    parse_champ_header(t_hdr *hdr, int fd)
{
    off_t   siz;

    if (fd < 0)
        return ;
    if ((siz = lseek(fd, 0, SEEK_END)) == -1)
        PERROR("lseek");
    if ((size_t)siz < sizeof(t_hdr))
        ERROR("Invalid header size\n");
    if (lseek(fd, 0, SEEK_SET) == -1)
        PERROR("lseek");
    if (read(fd, hdr, sizeof(t_hdr)) != sizeof(t_hdr))
        PERROR("read");
    rev_bytes(&hdr->magic, sizeof(hdr->magic));
	if (hdr->magic != COREWAR_EXEC_MAGIC)
	{
        printf("%x %x\n", hdr->magic, COREWAR_EXEC_MAGIC);
        ERROR("Invalid header\n");
    }
    rev_bytes(&hdr->prog_size, sizeof(hdr->prog_size));
	if (hdr->prog_size != siz - sizeof(t_hdr))
        ERROR("Invalid header\n");
	if (hdr->prog_size > CHAMP_MAX_SIZE)
	{
        printf("%d %d\n", hdr->prog_size, CHAMP_MAX_SIZE);
        ERROR("Champion too large\n");
    }
}

/**
 *  init a process and insert it at the beginning of the 
 *  process list.
 * 
 *  pid started at -1, the byte code is ffff ffff.
 * 
 *  need to assign the pid to the first register of the 
 *  process, so that the champion can call live with 
 *  the right value indicating that the process/champion
 *  with this pid is alive.
 * 
 * @param {t_vm} vm - current vm structure
 * @param {void *} pc - current program counter
 * 
 */

void    init_process(t_vm *vm, void * pc)
{
    t_process           *process;
    static int32_t      pid = -1;

    process = malloc(sizeof(t_process));
    bzero_(process, sizeof(t_process));
    process->pc = pc;
    process->pid = pid;
    process->registers[1] = pid;
    printf("initing... pid: %d\n", pid);
    pid++;
    if (vm->process_list)
        process->next = vm->process_list;
    vm->process_list = process;
    vm->nprocess++;
}

/**
 *  read .cor from command line, parse the info and load it
 *  into the memory
 *  
 *  parse the header of the champion file into t_hdr
 *  copy the name of the champion and the comment into 
 *  t_champ and the t_champ goes into t_vm.champions
 *  the id of the champion will be the same as pid of
 *  the process, but when displaying to the terminal
 *  we need to +2 to the value (pid start at -1, but
 *  it's also the 1st process aka "player 1")
 * 
 *  the acutal byte codes of the champion will be copied 
 *  into the arena (vm.memory), and the corresponding
 *  process will be initialized, as you know, 
 *  a process is the instance of a champion that
 *  is being executed 
 * 
 * @param {t_vm} vm - current vm structure
 * @param {int} fd - file descriptor of the file where the
 *      champion is stored
 * 
 */

void    load_champ(t_vm *vm, int fd)
{
    t_hdr               hdr;
    t_champ             *champ;
    static uint8_t      index;
    void                *pc;

    parse_champ_header(&hdr, fd);
    champ = &(vm->corewar.champions[index]);
	memcpy_(champ->name, hdr.prog_name, PROG_NAME_LENGTH);
	memcpy_(champ->comment, hdr.comment, COMMENT_LENGTH);
    champ->id = index - 1;
	pc = &vm->memory[(MEM_SIZE / vm->corewar.nplayers) * index];
	if (read(fd, pc, hdr.prog_size) != hdr.prog_size)
		PERROR("read");
    init_process(vm, pc);
    LOG("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",  champ->id + 2, 
        hdr.prog_size, champ->name, champ->comment);
    index++;
    close(fd);
}

void    print_mem(t_vm *vm)
{
    int                 i;
    unsigned            siz;

    i = 0;
    siz = (unsigned)sqrt(MEM_SIZE);
    while (i < 100) // < MEM_SZIE
    {
        if (i % siz == 0)
        {
            if (i)
                printf("\n");
            printf("%#06x : ", i);
        }
        puthex(vm->memory[i]);
        printf(" ");
        i++;
    }
    printf("\n");
}

void    loader(t_vm *vm, char *filename)
{
    int fd;

    if ((fd = open(filename, O_RDONLY)) == -1)
        PERROR("open"); 
    load_champ(vm, fd);
}