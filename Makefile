# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbernard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 16:22:44 by mbernard          #+#    #+#              #
#    Updated: 2024/02/14 19:21:05 by mbernard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = so_long
FLAGS = -lX11 -lXext -lGL

# ---------------------------------- Repertories ----------------------------- #
LIBX = libmlx_Linux.a
LIBX_DIR = minilibx-linux/
INCLUDES = ${LIBX_DIR}${LIBX}

vpath %c ./

SRCS = so_long.c

# ---------------------------------- Compilation ----------------------------- #
all: ${NAME}

${NAME}: ${OBJS} ${LIBX} 
	${CC} ${SRCS} ${INCLUDES} ${FLAGS}  -o $@
${LIBX}:
	make -C ${LIBX_DIR}
#
#${OBJS_DIR}%.o: %.c ${HEADER} | ${OBJS_DIR}
#	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@
#
#-include ${DEPS}

# ---------------------------------- Create Repertory ---------------------- #
#${OBJS_DIR}:
#	${MKDIR} ${OBJS_DIR}

# ---------------------------------- Clean ----------------------------------- #
#clean:
#	${RMDIR} ${OBJS_DIR}
#	${MAKE} clean -C $(LIBFT_DIR)

fclean: #clean
	${RM} ${NAME}
#	${RM} ${LIBFT}

re:    fclean
	${MAKE} ${NAME}

# ---------------------------------- Phony ----------------------------------- #
.PHONY: all fclean re
