/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:26:53 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/24 16:46:55 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void		*surveil(void *philpointer)
{
	t_phil		*phil;

	phil = (t_phil *)philpointer;
	while (!phil->info->someone_is_dead &&
		phil->times_eaten != phil->info->max_eat)
	{
		pthread_mutex_lock(&phil->eating);
		if (!phil->info->someone_is_dead &&
			phil->times_eaten != phil->info->max_eat &&
			get_time() - phil->last_eat > (uint64_t)phil->info->time_to_die)
		{
			message(phil, DEAD);
			pthread_mutex_lock(&phil->info->write);
			phil->info->someone_is_dead = 1;
			pthread_mutex_unlock(&phil->info->write);
		}
		pthread_mutex_unlock(&phil->eating);
		usleep(100);
	}
	return (NULL);
}

void		*start_phil(void *philpointer)
{
	pthread_t	surveiller;
	t_phil		*phil;
	int			can_eat_enough;

	phil = (t_phil *)philpointer;
	can_eat_enough = (phil->info->max_eat > 0) ? 1 : 0;
	pthread_create(&surveiller, NULL, surveil, philpointer);
	while (!phil->info->someone_is_dead)
	{
		eat(phil);
		if (can_eat_enough && phil->times_eaten == phil->info->max_eat)
		{
			message(phil, ENOUGH);
			pthread_mutex_lock(&phil->info->write);
			phil->info->phils_whos_eaten_enough++;
			pthread_mutex_unlock(&phil->info->write);
			pthread_mutex_destroy(&phil->eating);
			return (NULL);
		}
		message(phil, SLEEP);
		usleep(1000 * (phil->info->time_to_sleep));
		message(phil, THINK);
	}
	pthread_mutex_destroy(&phil->eating);
	return (NULL);
}

pthread_t	*start_program(t_info *info)
{
	t_phil		**phils;
	int			i;
	pthread_t	*threads;

	i = -1;
	threads = (pthread_t *)mmalloc(sizeof(pthread_t) * info->num_phil);
	phils = (t_phil **)mmalloc(sizeof(t_phil *) * info->num_phil);
	while (++i < info->num_phil)
	{
		phils[i] = (t_phil *)mmalloc(sizeof(t_phil));
		phils[i]->info = info;
		pthread_mutex_init(&phils[i]->eating, NULL);
		phils[i]->name = i + 1;
		phils[i]->last_eat = 0;
		phils[i]->times_eaten = 0;
	}
	i = -1;
	get_time();
	while (++i < info->num_phil)
	{
		pthread_create(&threads[i], NULL, start_phil, (void *)phils[i]);
		usleep(100);
	}
	return (threads);
}
