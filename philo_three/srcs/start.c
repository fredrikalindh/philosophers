/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:26:53 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/27 13:16:41 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void		*check_if_dead(void *philpointer)
{
	t_phil		*phil;

	phil = (t_phil *)philpointer;
	while (1)
	{
		if (!phil->eating && phil->times_eaten != phil->info.max_eat &&
			get_time() - phil->last_eat > (uint64_t)phil->info.time_to_die)
		{
			message(phil, DEAD);
			sem_wait(phil->info.dead);
			exit (1);
		}
		usleep(100);
	}
	return (NULL);
}

void		*start_phil(t_phil *phil)
{
	pthread_t	surveiller[2];
	int			can_eat_enough;

	can_eat_enough = (phil->info.max_eat > 0) ? 1 : 0;
	pthread_create(&surveiller[0], NULL, check_if_dead, (void *)phil);
	phil->last_eat = get_time();
	while (1)
	{
		eat(phil);
		if (can_eat_enough && phil->times_eaten == phil->info.max_eat)
		{
			message(phil, ENOUGH);
			exit(0);
		}
		message(phil, SLEEP);
		usleep(1000 * (phil->info.time_to_sleep));
		message(phil, THINK);
	}
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
			start_phil(phils[i]);
	}
	return (pids);
}
