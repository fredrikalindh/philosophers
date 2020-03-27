/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:39:25 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/25 16:48:47 by fredrikalindh    ###   ########.fr       */
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
# include <ft_printf.h>
# include <semaphore.h>
# include <signal.h>



typedef enum {
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	ENOUGH
} messages;

# define FORKS "forks"
# define WRITE "swrite"

typedef struct		s_info
{
	sem_t			*forks;
	sem_t			*write;
	sem_t			*dead;
	int				num_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
}					t_info;

typedef struct		s_phil
{
	int				name;
	uint64_t		last_eat;
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
uint64_t			get_time(void);
int					errormess(char *mess);
int					message(t_phil *phil, int type);

#endif
