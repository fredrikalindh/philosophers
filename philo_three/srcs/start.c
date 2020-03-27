/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:26:53 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/25 17:27:57 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void		*check_if_dead(void *philpointer)
{
	t_phil		*phil;

	phil = (t_phil *)philpointer;
	while (phil->times_eaten != phil->info.max_eat)
	{
		if (!phil->eating && phil->times_eaten != phil->info.max_eat &&
			get_time() - phil->last_eat > (uint64_t)phil->info.time_to_die)
		{
			message(phil, DEAD);
			sem_post(phil->info.dead);
		}
		usleep(100);
	}
	return (NULL);
}

void		*surveil(void *philpointer)
{
	t_phil		*phil;

	phil = (t_phil *)philpointer;
	sem_wait(phil->info.dead);
	exit(0);
}

void		*start_phil(t_phil *phil)
{
	pthread_t	surveiller[2];
	int			can_eat_enough;

	can_eat_enough = (phil->info.max_eat > 0) ? 1 : 0;
	pthread_create(&surveiller[0], NULL, check_if_dead, (void *)phil);
	pthread_create(&surveiller[1], NULL, surveil, (void *)phil);
	get_time();
	while (1)
	{
		eat(phil);
		if (can_eat_enough && phil->times_eaten == phil->info.max_eat)
		{
			message(phil, ENOUGH);
			exit(1);
		}
		message(phil, SLEEP);
		usleep(1000 * (phil->info.time_to_sleep));
		message(phil, THINK);
	}
	exit(1);
}

pid_t	*start_program(t_info info)
{
	t_phil		**phils;
	int			i;
	pid_t		*pids;

	i = -1;
	pids = (pid_t *)mmalloc(sizeof(pid_t) * info.num_phil);
	phils = (t_phil **)mmalloc(sizeof(t_phil *) * info.num_phil);
	while (++i < info.num_phil)
	{
		phils[i] = (t_phil *)mmalloc(sizeof(t_phil));
		phils[i]->info = info;
		phils[i]->name = i + 1;
		phils[i]->last_eat = 0;
		phils[i]->times_eaten = 0;
		phils[i]->eating = 0;
	}
	i = -1;
	get_time();
	while (++i < info.num_phil)
	{
		if ((pids[i] = fork()) < 0)
		{
			ft_printf("fork failed\n");
			exit(1);
		}
		if (!pids[i])
		{
			// usleep(10000 * (info.num_phil - i));
			start_phil(phils[i]);
		}
	}
	return (pids);
}
