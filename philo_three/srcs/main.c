/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:19:39 by fredrika          #+#    #+#             */
/*   Updated: 2020/10/27 12:25:03 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int		get_info(t_info *info, int ac, char **av)
{
	if ((info->num_phil = ft_atoi(av[1])) < 2 ||
	(info->time_to_die = ft_atoi(av[2])) < 0 ||
	(info->time_to_eat = ft_atoi(av[3])) < 0 ||
	(info->time_to_sleep = ft_atoi(av[4])) < 0)
		return (1);
	if (ac == 6 && (info->max_eat = ft_atoi(av[5])) <= 0)
		return (1);
	else if (ac == 5)
		info->max_eat = -1;
	sem_unlink("/sforks");
	sem_unlink("/swrite");
	sem_unlink("/sdead");
	sem_unlink("/ssomeone_picking");
	g_forks = sem_open("/sforks", O_CREAT, S_IRWXU, info->num_phil);
	g_write = sem_open("/swrite", O_CREAT, S_IRWXU, 1);
	g_dead = sem_open("/sdead", O_CREAT, S_IRWXU, 1);
	g_someone_picking = sem_open("/ssomeone_picking", O_CREAT, S_IRWXU, 1);
	return (0);
}

void	destroy_sem(void)
{
	sem_close(g_forks);
	sem_close(g_write);
	sem_close(g_dead);
	sem_close(g_someone_picking);
	sem_unlink("/sforks");
	sem_unlink("/swrite");
	sem_unlink("/sdead");
	sem_unlink("/ssomeone_picking");
}

int		main(int ac, char **av)
{
	t_info	info;
	pid_t	*pids;
	int		someones_dead;
	int		i;

	if (ac < 5 || ac > 6)
		return (errormess("error: wrong number of arguments"));
	if (get_info(&info, ac, av))
		return (errormess("error: arguments"));
	if (!(pids = start_program(info)))
		return (errormess("error: fatal"));
	while (!(someones_dead = 0))
	{
		if (waitpid(-1, &someones_dead, 0) < 0 || ((WIFEXITED(someones_dead)
				|| WIFSIGNALED(someones_dead)) && someones_dead))
		{
			i = -1;
			while (++i < info.num_phil)
				kill(pids[i], SIGINT);
			break ;
		}
	}
	destroy_sem();
	free(pids);
	return (0);
}
