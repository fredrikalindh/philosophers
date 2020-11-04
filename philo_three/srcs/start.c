/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:26:53 by fredrika          #+#    #+#             */
/*   Updated: 2020/11/04 10:53:47 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*check_if_dead(void *philpointer)
{
	t_phil	*phil;

	phil = (t_phil *)philpointer;
	while (1)
	{
		sem_wait(phil->eating);
		if (get_time(0) - phil->last_eat > (u_int64_t)phil->info.time_to_die)
		{
			if (phil->times_eaten != phil->info.max_eat)
			{
				message(phil->name, DEAD);
				sem_wait(g_dead);
				sem_post(phil->eating);
				exit(1);
			}
		}
		sem_post(phil->eating);
		usleep(100);
	}
	return (NULL);
}

void	ft_sync(int phils)
{
	while (get_time(0) < (u_int64_t)200 * phils)
		;
}

void	start_phil(t_phil phil, pid_t *pids)
{
	pthread_t surveiller;

	free(pids);
	ft_sync(phil.info.num_phil);
	phil.last_eat = get_time(1);
	pthread_create(&surveiller, NULL, check_if_dead, (void *)&phil);
	while (1)
	{
		eat(&phil);
		if (phil.times_eaten == phil.info.max_eat)
			exit(0);
		message(phil.name, SLEEP);
		real_sleep(phil.info.time_to_sleep);
		message(phil.name, THINK);
	}
}

pid_t	*start_program(t_info info)
{
	t_phil	phil;
	int		i;
	pid_t	*pids;

	i = -1;
	pids = (pid_t *)malloc(sizeof(pid_t) * info.num_phil);
	get_time(0);
	while (++i < info.num_phil)
	{
		phil.info = info;
		phil.name = i + 1;
		phil.times_eaten = 0;
		phil.eating = 0;
		phil.sem_name[0] = phil.name + '0';
		phil.sem_name[1] = '\0';
		sem_unlink(phil.sem_name);
		phil.eating = sem_open(phil.sem_name, O_CREAT, S_IRWXU, 1);
		if ((pids[i] = fork()) < 0)
			exit(errormess("fork failed\n"));
		if (!pids[i])
			start_phil(phil, pids);
	}
	return (pids);
}
