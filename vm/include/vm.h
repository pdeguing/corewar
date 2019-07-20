/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 02:32:06 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/13 17:30:30 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
#define VM_H

#include <unistd.h>
#include "common.h"
#include "op.h"
#include "handler.h"

#define ITERATOR -1
#define INC(num) (++num)
#define ONEBYTE 1
// #define EDI_TYPE (acb) (acb & 0b11000000)
// #define ESI_TYPE (acb) (acb & 0b00110000)
// #define ECX_TYPE (acb) (acb & 0b00001100)
#define REGISTER_TYPE 0b01000000
#define DIRECT_TYPE 0b10000000
#define INDIRECT_TYPE 0b11000000
#define GET_ACB_TYPE(acb) (acb & 0b11000000)
# define MAP_START g_base
# define MAP_END g_base + MEM_SIZE
#define FOR_EACH(item, array) typeof(*(array)) *start = array;\
                            typeof(*(array)) *end = (start + (sizeof(array) / sizeof*(array)) + 1);\
                            typeof(*(array)) *item;\
                            while ((item = start) && start++ != end )
# define READ_FROM_MEM(a, b, c, d) mem_oper(READ, (t_byte *)b, a, c); if (d) rev_bytes(b, c);
# define WRITE_TO_MEM(a, b, c, d) if(d == LITTLE_E)rev_bytes(a, c); mem_oper(WRITE, (t_byte *)a, (t_byte *)b, c); ;
# define READ_(i, b, c)  READ_FROM_MEM(i, b, c, BIG_E);
# define WRITE_(i, b, c)  WRITE_TO_MEM(i, b, c, LITTLE_E);
# define MEM_POX(a) mem_pos(a)
# define REL(pc, offset) MEM_POX(pc + (offset % IDX_MOD))
# define ABS(pc, offset)  MEM_POX(pc + offset)
# define LOG printf
# define LEA(reg, mem) read_arg(mem, &reg, false, false);
# define LLEA(reg, mem) read_arg(mem, &reg, false, true);
# define LD(reg, mem) read_arg(mem, &reg, true, false);
# define LLD(reg, mem) read_arg(mem, &reg, true, true);
# define EDI g_cur_process->registers[1]
# define ESI g_cur_process->registers[2]
# define ECX g_cur_process->registers[3]
# define ADD(reg1, reg2) reg1 += reg2
# define SUB(reg1, reg2) reg1 -= reg2
# define AND(reg1, reg2) reg1 &= reg2
# define OR(reg1, reg2) reg1 |= reg2
# define XOR(reg1, reg2) reg1 ^= reg2
# define MOV(r1, r2) WRITE_(&r1, &r2, 4);
// # define MOV
# define PC g_cur_process->cpc
# define CP g_cur_process
# define INSTR g_op_tab
# define REG(i) g_cur_process->registers[i]

typedef enum e_endianess
{
	LITTLE_E,
	BIG_E
}			t_endianess;

typedef enum e_mem_op
{
	READ,
	WRITE
}			t_mem_op;

// typedef struct 		s_cpu
// {
// 	t_arg_type   argvt[MAX_ARGS_NUMBER];
//     uint8_t      *argv[MAX_ARGS_NUMBER];
// }					t_cpu;

typedef struct		s_op
{
	char			*name;
	int				argc;
	t_arg_type		argvt[MAX_ARGS_NUMBER];
	char			opcode;
	uint32_t		cycles;
	char			*des;
	t_bool			coding_byte;
	t_bool			truncate;
}					t_op;

typedef struct		s_hdr
{
	uint32_t		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_hdr;

typedef struct 		s_task
{
	t_op			op_info;
	uint64_t		argv[MAX_ARGS_NUMBER];
}					t_task;


typedef struct      s_champ
{
	int32_t			id;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	uint32_t		lives;
	uint32_t 		last_live;
}                   t_champ;


typedef struct      	s_process
{
    t_word         		registers[REG_NUMBER + 1];
    t_byte            	*pc;
	t_byte 				*cpc;
    int32_t         	pid;
	t_champ				*champion;
	struct s_process	*next;
	t_bool				carry;
}                   	t_process;

typedef struct      s_cw
{
	uint32_t		cycle;
	t_champ			champions[MAX_PLAYERS];
	uint8_t			ownership[MEM_SIZE];
    uint8_t         nplayers;
	uint32_t		dump_cycle;
	uint32_t 		kill_cycle;
}                   t_cw;


typedef struct      s_vm
{
	uint8_t			memory[MEM_SIZE];
    t_process       *process_list;
	uint8_t			nprocess;
    t_cw            corewar;
	t_bool 			debug_mode;
}                   t_vm;

typedef	struct 		s_arg
{
	t_byte			*argv;
	t_byte			argvt;
}					t_arg;

typedef struct 		s_instr
{
	t_byte 			*pc;
	t_byte			instr;
	t_byte 			argc;
	t_byte			*argv[MAX_ARGS_NUMBER];
	t_byte			argvt[MAX_ARGS_NUMBER];
	t_arg			arg[MAX_ARGS_NUMBER];
	t_process		*context;
}					t_instr;


typedef void(*t_instr_hdlr)(t_vm *, t_instr *);

extern t_op g_op_tab[17];
extern uint8_t	*g_base;
extern t_process *g_cur_process;

// parser
void			parse_champ_header(t_hdr *hdr, int fd);

// helper 
void    		rev_bytes(void *ptr, size_t n);
void			puthex(unsigned char c);

void    		print_mem(t_vm *vm);
void			bzero_(void *rsi, size_t rcx);
//loader
void    		loader(t_vm *vm, char *filename);

//process
void    		process_loop(t_vm   *vm);
void    		fork_process(t_vm *vm, t_process *parent, int32_t offset, t_bool far);

// champion
t_champ			*search_champion(t_vm *vm, int32_t id);


// memory 

t_byte 			*mem_pos(t_byte *pos);
void 			mem_oper(t_mem_op op, t_byte *dst, t_byte *src, uint8_t cnt);
void    		read_m(void *fd, void *buff, unsigned int size);
void    		write_m(void *fd, void *buff, unsigned int size);
void    		read_arg(t_arg *arg, int32_t *buff, t_bool addressing, t_bool far);
#endif