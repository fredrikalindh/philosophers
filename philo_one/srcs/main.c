/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:19:39 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/24 17:16:53 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>

int		get_info(t_info *info, int ac, char **av)
{
	if ((info->num_phil = ft_atoi(av[1])) < 2 ||
	(info->time_to_die = ft_atoi(av[2])) < 0 ||
	(info->time_to_eat = ft_atoi(av[3]))  < 0||
	(info->time_to_sleep = ft_atoi(av[4])) < 0)
		return (1);
	if (ac == 6 && (info->max_eat = ft_atoi(av[5])) <= 0)
		return (1);
	else if (ac == 5)
		info->max_eat = -1;
	info->forks =
	(pthread_mutex_t *)mmalloc(sizeof(pthread_mutex_t) * info->num_phil);
	ac = -1;
	while (++ac < info->num_phil)
		pthread_mutex_init(&info->forks[ac], NULL);
	info->someone_is_dead = 0;
	info->phils_whos_eaten_enough = 0;
	pthread_mutex_init(&info->write, NULL);
	return (0);
}

void	destroy_mutexes(t_info info, int num)
{
	while (num-- > 0)
		pthread_mutex_destroy(&info.forks[num]);
	pthread_mutex_destroy(&info.write);
}

int		main(int ac, char **av)
{
	t_info		info;
	pthread_t	*threads;

	if (ac < 5 || ac > 6)
		return (errormess("error: wrong number of arguments"));
	if (get_info(&info, ac, av))
		return (errormess("error: arguments"));
	if (!(threads = start_program(&info)))
		return (errormess("error: fatal"));
	while (!info.someone_is_dead &&
		info.phils_whos_eaten_enough < info.num_phil)
		usleep(100);
	while (info.num_phil-- > 0)
		pthread_join(threads[info.num_phil], NULL);
	destroy_mutexes(info, info.num_phil);
	free_all_malloc();
	return (0);
}
