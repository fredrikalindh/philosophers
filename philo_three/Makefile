# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/08 16:41:33 by fredrika          #+#    #+#              #
#    Updated: 2020/10/27 11:50:41 by fredrikalindh    ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *** NAME - CC - FLAGS ****************************************************** #

NAME					=	philo_three

CC						=	clang

FLAGS					=	-Wall -Wextra -Werror


# *** PROJECT HEADER ********************************************************* #

HDIR					=	$(addprefix -I, $(HEADER_DIR))

HEADER_DIR				=	\
							./includes/

HEADER					=	philo.h

# *** SRCS ******************************************************************* #

SRCS_DIR				=	./srcs/

SRCS_LIST				=	main.c \
							messages.c \
							eat.c \
							start.c \
							utils.c \
							ft_atoi.c \

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
