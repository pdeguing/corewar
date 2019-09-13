/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 23:01:36 by qpeng             #+#    #+#             */
/*   Updated: 2019/08/04 14:54:25 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    h_rev_bytes(void *ptr, size_t n)
{
	size_t	i;
	size_t  half;
	uint8_t *tmp;
	uint8_t swap;

	i = 0;
	half = n / 2;
	tmp = (uint8_t *)ptr;
	while (i < half)
	{
		swap = tmp[i];
		tmp[i] = tmp[n - i - 1];
		tmp[n - i - 1] = swap;
		++i;
	}
}

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	h_puthex(unsigned char c, t_gui *gui, int x, int y)
{
	// (void)c;
    static char    *base = "0123456789abcdef";

	// ft_putchar(base[c / 16]);
	// ft_putchar(base[c % 16]);
	// init_pair(1, COLOR_GREEN, COLOR_BLACK);
    // wattron(gui->win, COLOR_PAIR(1));
	mvwprintw(gui->win, y, x, "%c%c ", base[c / 16], base[c % 16]);
	// wattroff(gui->win, COLOR_PAIR(1));
}

void    h_print_register(t_process *cp)
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