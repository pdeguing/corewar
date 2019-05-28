/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:02:38 by anjansse          #+#    #+#             */
/*   Updated: 2019/05/25 14:58:08 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoinfree1(char *s1, char *s2)
{
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	ft_strdel(&s1);
	return (s3);
}
