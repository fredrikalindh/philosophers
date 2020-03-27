/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:19:39 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/27 13:45:29 by fredrikalindh    ###   ########.fr       */
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
	sem_unlink("/sforks");
	sem_unlink("/swrite");
	sem_unlink("/sdead");
	info->forks = sem_open("/sforks", O_CREAT, S_IRWXU, info->num_phil);
	info->write = sem_open("/swrite", O_CREAT, S_IRWXU, 1);
	info->dead = sem_open("/sdead", O_CREAT, S_IRWXU, 1);
	info->someone_is_dead = 0;
	return (0);
}

void	destroy_sem(t_info info)
{
	sem_close(info.forks);
	sem_close(info.write);
	sem_close(info.dead);
	sem_unlink("/sforks");
	sem_unlink("/swrite");
	sem_unlink("/sdead");
}

int		main(int ac, char **av)
{
	t_info		info;
	pid_t		*pids;
	int			signal;
	int			i;

	if (ac < 5 || ac > 6)
		return (errormess("error: wrong number of arguments"));
	if (get_info(&info, ac, av))
		return (errormess("error: arguments"));
	if (!(pids = start_program(info)))
		return (errormess("error: fatal"));
	signal = 0;
	i = 0;
	while (!signal && i++ < info.num_phil)
	{
		wait(&signal);
		signal = WEXITSTATUS(signal);
	}
	while (info.num_phil-- > 0)
		kill(pids[info.num_phil], SIGKILL);
	destroy_sem(info);
	free_all_malloc();
	return (0);
}
