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
		sem_wait(phil->eating);
		if (phil->times_eaten != phil->info.max_eat &&
			get_time() - phil->last_eat > (u_int64_t)phil->info.time_to_die)
		{
			message(phil->name, DEAD);
			sem_wait(g_dead);
			free_all_malloc();
			exit(1);
		}
		sem_post(phil->eating);
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
		if (phil.times_eaten == phil.info.max_eat)
		{
			message(phil.name, ENOUGH);
			free_all_malloc();
			exit(0);
		}
		message(phil.name, SLEEP);
		real_sleep(phil.info.time_to_sleep);
		message(phil.name, THINK);
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
		phil.sem_name[0] = phil.name + '0';
		phil.sem_name[1] = '\0';
		sem_unlink(phil.sem_name);
		phil.eating = sem_open(phil.sem_name, O_CREAT, S_IRWXU, 1);
		if ((pids[i] = fork()) < 0)
			exit(errormess("fork failed\n"));
		if (!pids[i])
			start_phil(phil);
	}
	while (--i >= 0)
		sem_post(g_start);
	return (pids);
}
// t_phil	*start_program(t_info info)
// {
// 	t_phil		*phils;
// 	int			i;
// 	// pid_t		*pids;

// 	i = -1;
// 	// pids = (pid_t *)mmalloc(sizeof(pid_t) * info.num_phil);
// 	phils = (t_phil *)mmalloc(sizeof(t_phil) * info.num_phil);
// 	while (++i < info.num_phil)
// 	{
// 		phils[i].info = info;
// 		phils[i].name = i + 1;
// 		phils[i].times_eaten = 0;
// 		phils[i].eating = 0;
// 		phils[i].sem_name[0] = phils[i].name + '0';
// 		phils[i].sem_name[1] = '\0';
// 		sem_unlink(phils[i].sem_name);
// 		phils[i].eating = sem_open(phils[i].sem_name, O_CREAT, S_IRWXU, 1);
// 		if ((phils[i].pid = fork()) < 0)
// 			exit(errormess("fork failed\n"));
// 		if (!phils[i].pid)
// 			start_phil(&phils[i]);
// 	}
// 	while (--i >= 0)
// 		sem_post(g_start);
// 	return (phils);
// }
