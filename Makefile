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
FLAGS = -lX11 -lXext #-lGL
CFLAGS = -Wall -Wextra -Werror -MMD -MP
MKDIR = mkdir -p
RMDIR = rm -rf

# ---------------------------------- Sources --------------------------------- #
vpath %c ./

SRCS = so_long
# ---------------------------------- Repertories ----------------------------- #
HEADER_DIR = header/
OBJS_DIR = .objs/
HEADER = $(addprefix ${HEADER_DIR}, so_long.h)
OBJS = $(addprefix ${OBJS_DIR}, $(addsuffix .o, ${SRCS}))
DEPS = ${OBJS:.o=.d}

# ---------------------------------- LibX Gestion ----------------------------- #
LIBX = libmlx_Linux.a
LIBX_DIR = minilibx-linux/
LINK_LIBX = -L ${LIBX_DIR} -lmlx_Linux
INCLUDES = -I ${LIBX_DIR} -I ${HEADER_DIR}

# ---------------------------------- Compilation ----------------------------- #
all: ${NAME}

${NAME}: ${OBJS} ${LIBX}
	${CC} ${CFLAGS} ${OBJS} ${INCLUDES} ${LINK_LIBX} ${FLAGS}  -o $@

${OBJS_DIR}%.o: %.c ${HEADER} | ${OBJS_DIR}
	${CC} ${CFLAGS} ${INCLUDES} ${LINK_LIBX} -O3 -c $< -o $@

${LIBX}: ${FORCE}
	make -C ${LIBX_DIR}
-include ${DEPS}

# ---------------------------------- Create Repertory ---------------------- #
${OBJS_DIR}:
			${MKDIR} ${OBJS_DIR}

## ---------------------------------- Clean ----------------------------------- #
clean:  ${OBJS_DIR}
	${RMDIR} ${OBJS_DIR}
	${MAKE} clean -C $(LIBX_DIR)

fclean: clean
	${RM} ${NAME}
	${RM} ${LIBX}

re:    fclean
	${MAKE} ${NAME}

FORCE:

# ---------------------------------- Phony ----------------------------------- #
.PHONY: all clean fclean re FORCE
