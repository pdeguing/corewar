/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:37:29 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/14 17:55:49 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_arg		*create_key(t_arg *key, char *str, int beg)
{
	int		index;

	key->index = beg;
	index = key->index;
	if (check_flags(str[key->index]))
		key = flags_key(key, str, key->index);
	if (check_width(str[key->index]))
		key = width_key(key, str, key->index);
	if (check_prec(str[key->index]))
		key = prec_key(key, str, key->index);
	if (check_length(str[key->index]))
		key = length_key(key, str, key->index);
	if (check_specs(str[key->index]))
		key = specs_key(key, str, key->index);
	return (key);
}
