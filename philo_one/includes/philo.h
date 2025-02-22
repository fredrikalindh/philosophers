/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:39:25 by fredrika          #+#    #+#             */
/*   Updated: 2020/10/27 12:11:57 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DEAD "died\n"

typedef struct			s_info
{
	int					someone_is_dead:1;
	pthread_mutex_t		write;
	pthread_mutex_t		*forks;
	int					num_phil;
	int					phils_whos_eaten_enough;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	int					start:1;
}						t_info;

typedef struct			s_phil
{
	int					name;
	unsigned long long	last_eat;
	int					times_eaten;
	pthread_mutex_t		is_eating;
	pthread_mutex_t		*f1;
	pthread_mutex_t		*f2;
	t_info				*info;
	pthread_t			thread;
}						t_phil;

typedef struct			s_list
{
	void				*data;
	struct s_list		*next;
}						t_list;

int						ft_atoi(char *str);
void					eat(t_phil *phil);
t_phil					**start_program(t_info *info);
u_int64_t				get_time(void);
void					real_sleep(u_int64_t n);
int						errormess(char *mess);
int						message(t_phil *phil, char *message);

#endif
