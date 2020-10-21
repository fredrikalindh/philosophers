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
# include <semaphore.h>
# include <signal.h>
# include <limits.h>

# define FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DEAD "died\n"
# define ENOUGH "has eaten enough\n"

# define TIME_TO_SYNC 1000

sem_t			*g_forks;
sem_t			*g_start;
sem_t			*g_write;
sem_t			*g_dead;
sem_t			*g_someone_picking;

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
	char			sem_name[2];
	sem_t			*eating;
	t_info			info;
	pid_t			pid;
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
u_int64_t			get_time(int reset);
void				real_sleep(u_int64_t n);
int					errormess(char *mess);
int					message(int name, char *message);

#endif
