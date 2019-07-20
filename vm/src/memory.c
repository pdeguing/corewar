/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 20:01:05 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/13 16:42:43 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/**
 *  check if the pointer exceeds the end of the map
 *  if yes, then the exceeded part will be count 
 *  from the beginning, therefore making it
 *  "cicurlar"
 * 
 * @param {t_byte} pos - the memory position 
 *      that will be evaluated
 */

t_byte *mem_pos(t_byte *pos)
{
    if (pos > MAP_END)
        return (MAP_START + (pos - MAP_END));
    return (pos);
}

/**
 *  perform read/write operation to the map
 *  the map is circular so if read exceeds the 
 *  max size of the map, it will read from the 
 *  beginning of the map
 * 
 *  both dst and src can be either the map 
 *  or the buffer, it's just moving data 
 *  from one place to the other
 * 
 * @param {t_mem_op} op - memory operation
 * @param {t_byte} dst - destination
 * @param {t_byte} src - source 
 * @param {uint8_t} cnt - length of the buffer
 * 
 */

void    mem_oper(t_mem_op op, t_byte *dst, t_byte *src, uint8_t cnt)
{
    while (cnt--)
    {
        if (op == READ)
            src =  src + 1 > MAP_END ? MAP_START : src;
        else 
            dst = dst + 1 > MAP_END ? MAP_START : dst;
        *dst++ = *src++;
    }
}

/**
 *  read arg from the memory and place the result 
 *  into the buff
 * 
 * @param {t_arg} arg - arg structure that contains the 
 *      info about each arguments and its type
 * @param {int32_t} buff - generic buffer that can 
 *      store size of data up to 4 bytes
 * @param {t_bool} addressing - whather this 
 *      read is in "addressing mode", which means
 *      the value read as argument will be intrepreted 
 *      as address/meta info and the corresponding 
 *      operation will be perform, such as: an extra 
 *      read will be performed in case of indirect 
 *      type argument, the value of the specific 
 *      register will be copied into the buffer in case
 *      of register type value
 * @param {t_bool} far - whather when calculate 
 *      the address will be "% IDX_MOD"
 * 
 */

void    read_arg(t_arg *arg, int32_t *buff, t_bool addressing, t_bool far)
{
    int32_t     tmp;

    *buff = 0;
    tmp = 0;
    if (arg->argvt == INDIRECT_TYPE)
    {
        READ_(arg->argv, &tmp, 2);
        *buff = tmp;
        if (addressing)
            READ_(far ? REL(PC, tmp) : ABS(PC, tmp), buff, 4);
    }
    else if (arg->argvt == DIRECT_TYPE)
    {
        READ_(arg->argv, buff, INSTR[*PC - 1].truncate ? 2 : 4);
    }
    else
    {
        READ_(arg->argv, buff, 1);
        if (addressing)
            *buff = CP->registers[*buff];
    }
}

// void    read_m(void *fd, void *buff, unsigned int size)
// {
//     mem_oper(READ, (t_byte *)buff, (t_byte *)fd, size);
//     rev_bytes(buff, size);
// }

// void    write_m(void *fd, void *buff, unsigned int size)
// {
//     mem_oper(WRITE, (t_byte *)fd, (t_byte *)buff, size);
//     rev_bytes(fd, size);
// }