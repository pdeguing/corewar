/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 00:02:03 by anjansse          #+#    #+#             */
/*   Updated: 2019/05/25 00:46:05 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** All macros analysed in ressources ".s" files, with the help of the pdf.
** Ajoutes en d'autres si t'en trouves haha. (CHECK OP.C)
*/

#ifndef ASM_H
# define ASM_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../../libft/includes/libft.h"

# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz0123456789"

# define COMMENT_CHAR '#'
# define SEPARATOR_CHAR ','
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'

# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"

#endif
