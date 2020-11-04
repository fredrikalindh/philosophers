/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:26:53 by fredrika          #+#    #+#             */
/*   Updated: 2020/11/04 10:19:58 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void		*surveil(void *philpointer)
{
	t_phil *phil;

	phil = (t_phil *)philpointer;
	while (!phil->info->someone_is_dead &&
		phil->times_eaten != phil->info->max_eat)
	{
		pthread_mutex_lock(&phil->is_eating);
		if (!phil->info->someone_is_dead &&
			phil->times_eaten != phil->info->max_eat &&
			get_time() - phil->last_eat >
			(u_int64_t)phil->info->time_to_die)
		{
			message(phil, DEAD);
			phil->info->someone_is_dead = 1;
			break ;
		}
		pthread_mutex_unlock(&phil->is_eating);
		usleep(100);
	}
	pthread_mutex_unlock(phil->f1);
	pthread_mutex_unlock(phil->f2);
	pthread_mutex_unlock(&phil->is_eating);
	return (NULL);
}

void		*start_phil(void *philpointer)
{
	pthread_t	surveiller;
	t_phil		*phil;

	phil = (t_phil *)philpointer;
	while (!phil->info->start)
		;
	pthread_create(&surveiller, NULL, surveil, philpointer);
	while (!phil->info->someone_is_dead)
	{
		eat(phil);
		if (!phil->info->someone_is_dead &&
			phil->times_eaten == phil->info->max_eat)
		{
			pthread_mutex_lock(&phil->info->write);
			phil->info->phils_whos_eaten_enough++;
			pthread_mutex_unlock(&phil->info->write);
			break ;
		}
		message(phil, SLEEP);
		real_sleep(phil->info->time_to_sleep);
		message(phil, THINK);
	}
	pthread_join(surveiller, NULL);
	pthread_mutex_destroy(&phil->is_eating);
	return (NULL);
}

t_phil		**start_program(t_info *info)
{
	t_phil		**phils;
	int			i;

	i = -1;
	phils = (t_phil **)malloc(sizeof(t_phil *) * info->num_phil);
	while (++i < info->num_phil)
	{
		phils[i] = (t_phil *)malloc(sizeof(t_phil));
		phils[i]->info = info;
		phils[i]->name = i + 1;
		phils[i]->last_eat = 0;
		phils[i]->times_eaten = 0;
		phils[i]->f1 = &info->forks[i];
		phils[i]->f2 = &info->forks[(i + 1) % info->num_phil];
		pthread_mutex_init(&phils[i]->is_eating, NULL);
	}
	i = -1;
	info->start = 0;
	while (++i < info->num_phil)
		pthread_create(&phils[i]->thread, NULL, start_phil, (void *)phils[i]);
	info->start = 1;
	get_time();
	return (phils);
}
