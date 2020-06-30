/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:39:25 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/27 13:52:43 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <ft_printf.h>

typedef enum			e_messages
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	ENOUGH
}						t_messages;

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
	int					is_eating;
	pthread_mutex_t		*f1;
	pthread_mutex_t		*f2;
	t_info				*info;
}						t_phil;

typedef struct			s_list
{
	void				*data;
	struct s_list		*next;
}						t_list;

int						free_all_malloc(void);
int						ft_atoi(char *str);
void					*mmalloc(unsigned int size);
void					eat(t_phil *phil);
pthread_t				*start_program(t_info *info);
unsigned long long		get_time(void);
void					real_sleep(u_int64_t n);
int						errormess(char *mess);
int						message(t_phil *phil, int type);

#endif
