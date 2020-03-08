/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:39:25 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/08 21:42:21 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <ft_printf.h>

typedef	struct	s_info
{
	int				num_phil;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	long int		start_program;
	int				max_eat;
}				t_info;

typedef struct	s_phil
{
	int				name;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	useconds_t		time_to_die;
	int				times_eaten;
	t_info			info;
}				t_phil;

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

extern t_list		*g_all_malloc;

void				*mmalloc(unsigned int size);
int					free_all_malloc(void);
int					mfree(void **to_free);
int					ft_atoi(char *str);

#endif
