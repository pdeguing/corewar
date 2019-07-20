# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anjansse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:57:22 by anjansse          #+#    #+#              #
#    Updated: 2019/07/12 12:44:59 by anjansse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= asm
GENERAL		= main.c assembler.c parser.c parserHelpers.c lexer.c op.c \
		  writer.c vector.c get_args.c get_label.c get_instruction.c \
		  debug.c feed_references.c
SRCS		= $(addprefix src/, $(GENERAL))

INCLUDES	= -I include/

CC		= gcc

CFLAGS		= -Wall -Wextra -Werror

LLIB		= libft.a

all: $(NAME)

$(NAME):
	@echo ""
	@echo -n 'Compiling Program...'
	@cp ../libft/libft.a .
	@$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) $(LLIB) -o $(NAME)
	@echo "\t\x1b[92m✓✓\x1b[0m\n"

totall: lib all

lib:
	@echo -n 'Compiling libft...'
	@make -C ../libft/ re
	@cp ../libft/libft.a .
	@echo "\t\x1b[92m✓\x1b[0m\n"

.PHONY: all clean fclean re
git:
	@git add .
	@git commit -m "$(C)"
	@git push

clean:
	@rm -rf build

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LLIB)
	@echo "\t\n\x1b[96mASM \x1b[91mlibrary has been cleaned!\x1b[0m\n"

totfclean: fclean
	@make -C libft/ fclean
	@echo "\x1b[96mLibft has been cleaned.\x1b[0m\t\x1b[91mDon't forget to\
		recompile it...\n\x1b[0m"

re: fclean all

tot: totfclean totall
