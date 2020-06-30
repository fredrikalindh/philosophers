# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/08 16:41:33 by fredrika          #+#    #+#              #
#    Updated: 2020/03/24 17:17:27 by fredrikalindh    ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *** NAME - CC - FLAGS ****************************************************** #

NAME					=	philo_one

CC						=	gcc

FLAGS					=	-Wall -Wextra -Werror \
							-g3 -fsanitize=address \
							# -lpthread \


# *** PROJECT HEADER ********************************************************* #

HDIR					=	$(addprefix -I, $(HEADER_DIR))

HEADER_DIR				=	\
							./includes/

HEADER					=	philo.h \
							ft_printf.h \

# *** SRCS ******************************************************************* #

SRCS_DIR				=	./srcs/

SRCS_PRINTF				=	\
							ft_printf/to_n.c \
							ft_printf/skip_atoi.c \
							ft_printf/ft_strnlen.c \
							ft_printf/to_c.c \
							ft_printf/ft_printf.c \
							ft_printf/to_nbr.c \
							ft_printf/to_s.c \

SRCS_LIST				=	main.c \
							messages.c \
							eat.c \
							start.c \
							utils.c \
							mmalloc.c \
							ft_atoi.c \
							$(SRCS_PRINTF)

SRCS					=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

# *** OBJS ******************************************************************* #

OBJS_DIR				=	./objs/

OBJS_LIST				=	$(patsubst %.c, %.o, $(SRCS_LIST))

OBJS					=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

# *** RULES ****************************************************************** #

.PHONY: clean fclean all re norm test

all: $(OBJS) $(SRCS) $(NAME)

$(NAME): $(OBJS) $(SRCS)
	@ $(CC) $(FLAGS) $(HDIR) $(OBJS) -o $@ -lpthread

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(FLAGS) $(HDIR) -c -o $@ $<

norm:
	@ norminette $(SRCS_LIST) $(HEADER)

clean:
	@ rm -rf $(OBJS_DIR)

fclean: clean
	@ rm -f $(NAME)

re: fclean all
