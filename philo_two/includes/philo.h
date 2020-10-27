/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:39:25 by fredrika          #+#    #+#             */
/*   Updated: 2020/10/27 12:12:17 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>

# define FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DEAD "died\n"

typedef struct		s_info
{
	sem_t			*forks;
	sem_t			*write;
	sem_t			*someone_picking;
	int				someone_is_dead:1;
	int				start:1;
	int				num_phil;
	int				phils_whos_eaten_enough;
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
	t_info			*info;
	pthread_t		thread;
}					t_phil;

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

int					ft_atoi(char *str);
void				eat(t_phil *phil);
t_phil				**start_program(t_info *info);
u_int64_t			get_time(void);
void				real_sleep(u_int64_t n);
int					errormess(char *mess);
int					message(t_phil *phil, char *message);

#endif
