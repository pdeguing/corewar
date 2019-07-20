/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:02:14 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/12 22:17:11 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/**
 *  search through process list, find 
 *  the champion with the specific id and return 
 *  it 
 * 
 * @param {t_vm} vm - current vm structure
 * @param {int32_t} id - targeted champion's id
 */

t_champ *search_champion(t_vm *vm, int32_t id)
{
    FOR_EACH(champ, vm->corewar.champions)
    {
        if (champ->id == id)
            return champ;
    }
    return (NULL);
}

