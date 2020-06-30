/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:26:53 by fredrika          #+#    #+#             */
/*   Updated: 2020/04/15 23:20:18 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*check_if_dead(void *philpointer)
{
	t_phil		*phil;

	phil = (t_phil *)philpointer;
	while (1)
	{
		if (!phil->eating && phil->times_eaten != phil->info.max_eat &&
			get_time() - phil->last_eat > (u_int64_t)phil->info.time_to_die)
		{
			message(phil, DEAD);
			sem_wait(g_dead);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}

void	start_phil(t_phil phil)
{
	pthread_t	surveiller;

	sem_wait(g_start);
	phil.last_eat = get_time();
	pthread_create(&surveiller, NULL, check_if_dead, (void *)&phil);
	while (1)
	{
		eat(&phil);
		if (phil.info.max_eat > 0 && phil.times_eaten == phil.info.max_eat)
		{
			message(&phil, ENOUGH);
			exit(0);
		}
		message(&phil, SLEEP);
		usleep(1000 * (phil.info.time_to_sleep));
		message(&phil, THINK);
	}
}

pid_t	*start_program(t_info info)
{
	t_phil		phil;
	int			i;
	pid_t		*pids;

	i = -1;
	pids = (pid_t *)mmalloc(sizeof(pid_t) * info.num_phil);
	while (++i < info.num_phil)
	{
		phil.info = info;
		phil.name = i + 1;
		phil.times_eaten = 0;
		phil.eating = 0;
		if ((pids[i] = fork()) < 0)
		{
			ft_printf("fork failed\n");
			exit(1);
		}
		if (!pids[i])
			start_phil(phil);
	}
	while (i--)
	{
		sem_post(g_start);
	}
	return (pids);
}
