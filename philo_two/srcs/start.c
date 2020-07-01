/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:26:53 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/27 14:18:32 by fredrikalindh    ###   ########.fr       */
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
		sem_wait(phil->eating);
		if (!phil->info->someone_is_dead &&
			phil->times_eaten != phil->info->max_eat &&
			get_time() - phil->last_eat > (u_int64_t)phil->info->time_to_die)
		{
			message(phil, DEAD);
			phil->info->someone_is_dead = 1;
			sem_close(phil->eating);
			sem_unlink(phil->sem_name);
			return (NULL);
		}
		sem_post(phil->eating);
		usleep(1000);
	}
	sem_close(phil->eating);
	sem_unlink(phil->sem_name);
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
		if (phil->times_eaten == phil->info->max_eat)
		{
			message(phil, ENOUGH);
			sem_wait(phil->info->write);
			phil->info->phils_whos_eaten_enough++;
			sem_post(phil->info->write);
			return (NULL);
		}
		message(phil, SLEEP);
		usleep(1000 * (phil->info->time_to_sleep));
		message(phil, THINK);
	}
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
		phils[i]->name = i + 1;
		phils[i]->sem_name[0] = phils[i]->name + '0';
		phils[i]->sem_name[1] = '\0';
		phils[i]->last_eat = 0;
		phils[i]->times_eaten = 0;
		phils[i]->eating = sem_open(phils[i]->sem_name, O_CREAT, S_IRWXU, 1);
		// phils[i]->eating = 0;

	}
	i = -1;
	info->start = 0;
	while (++i < info->num_phil)
		pthread_create(&threads[i], NULL, start_phil, (void *)phils[i]);
	info->start = 1;
	get_time();
	return (threads);
}
