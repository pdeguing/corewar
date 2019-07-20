/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:20:54 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/13 17:18:02 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
#define HANDLER_H

#include "vm.h"

typedef struct s_vm t_vm;
typedef struct s_instr t_instr;

void    ft_live(t_vm *, t_instr *);
void    ft_ld(t_vm *, t_instr *);
void    ft_st(t_vm *, t_instr *);
void    ft_add(t_vm *, t_instr *);
void    ft_sub(t_vm *, t_instr *);
void    ft_and(t_vm *, t_instr *);
void    ft_or(t_vm *, t_instr *);
void    ft_xor(t_vm *, t_instr *);
void    ft_zjmp(t_vm *, t_instr *);
void    ft_ldi(t_vm *, t_instr *);
void    ft_sti(t_vm *, t_instr *);
void    ft_fork(t_vm *, t_instr *);
void    ft_lld(t_vm *, t_instr *);
void    ft_lldi(t_vm *, t_instr *);
void    ft_lfork(t_vm *, t_instr *);
void    ft_aff(t_vm *, t_instr *);

#endif