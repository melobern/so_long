# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbernard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 16:22:44 by mbernard          #+#    #+#              #
#    Updated: 2024/03/03 16:23:34 by mbernard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = so_long
FLAGS = -lX11 -lXext -lz
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3
MKDIR = mkdir -p
RMDIR = rm -rf

# ---------------------------------- Sources --------------------------------- #
vpath %c src

SRCS =	so_long	errors	utils	init		\
	moves	players_moves				\
	map	map_utils	check_map	fill_paths	
# ---------------------------------- Repertories ----------------------------- #
HEADER_DIR = header/
OBJS_DIR = .objs/
HEADER = $(addprefix ${HEADER_DIR}, so_long.h)
OBJS = $(addprefix ${OBJS_DIR}, $(addsuffix .o, ${SRCS}))
DEPS = ${OBJS:.o=.d}

# ---------------------------------- LibX Gestion ----------------------------- #
LIBX_DIR = minilibx-linux/
LINK_LIBX = -L ${LIBX_DIR} -lmlx_Linux
LINK_LIBFT = -L ${LIBFT_DIR} -lft
LIBFT_DIR = Libft/
LIBX = $(addprefix ${LIBX_DIR}, libmlx_Linux.a)
LIBFT = $(addprefix ${LIBFT_DIR}, libft.a)
INCLUDES = -I ${LIBX_DIR} -I ${HEADER_DIR} -I ${LIBFT_DIR}
LIBS = ${LINK_LIBX} ${LINK_LIBFT}

# ---------------------------------- Compilation ----------------------------- #
all: ${NAME}

${NAME}: ${OBJS} ${LIBX} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${INCLUDES} ${LIBS} ${FLAGS} -o $@

${OBJS_DIR}%.o: %.c ${HEADER} | ${OBJS_DIR}
	${CC} ${CFLAGS} ${INCLUDES} -O3 -c $< -o $@

${LIBX}: FORCE
	make -C ${LIBX_DIR}

${LIBFT}: FORCE
	$(MAKE) -C ${LIBFT_DIR}

-include ${DEPS}
# ---------------------------------- Create Repertory ---------------------- #
${OBJS_DIR}:
			${MKDIR} ${OBJS_DIR}

## ---------------------------------- Clean ----------------------------------- #
clean:  ${OBJS_DIR}
	${RMDIR} ${OBJS_DIR}
	${MAKE} clean -C $(LIBX_DIR)
	${MAKE} clean -C $(LIBFT_DIR)

fclean: clean
	${RM} ${NAME}
	${RM} ${LIBX}
	${RM} ${LIBFT}

re:    fclean
	${MAKE} ${NAME}

FORCE:

# ---------------------------------- Phony ----------------------------------- #
.PHONY: all clean fclean re FORCE
