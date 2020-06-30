/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:39:25 by fredrika          #+#    #+#             */
/*   Updated: 2020/04/15 23:11:13 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <pthread.h>
# include <ft_printf.h>
# include <semaphore.h>
# include <signal.h>

typedef enum	e_messages {
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	ENOUGH
}				t_messages;

sem_t			*g_forks;
sem_t			*g_start;
sem_t			*g_write;
sem_t			*g_dead;

typedef struct		s_info
{
	int				num_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
}					t_info;

typedef struct		s_phil
{
	int				name;
	u_int64_t		last_eat;
	int				times_eaten;
	int				eating;
	t_info			info;
}					t_phil;

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

int					free_all_malloc(void);
int					ft_atoi(char *str);
void				*mmalloc(unsigned int size);
void				eat(t_phil *phil);
pid_t				*start_program(t_info info);
u_int64_t			get_time(void);
int					errormess(char *mess);
int					message(t_phil *phil, int type);

#endif
