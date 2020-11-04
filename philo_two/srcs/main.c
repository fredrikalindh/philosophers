/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:19:39 by fredrika          #+#    #+#             */
/*   Updated: 2020/11/04 09:59:18 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>

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
	info->someone_is_dead = 0;
	info->phils_whos_eaten_enough = 0;
	sem_unlink("/sforks");
	sem_unlink("/swrite");
	sem_unlink("/ssomeone_picking");
	if (!(info->forks = sem_open("/sforks", O_CREAT, S_IRWXU, info->num_phil)))
		printf("error with sem open\n");
	info->write = sem_open("/swrite", O_CREAT, S_IRWXU, 1);
	info->someone_picking = sem_open("/ssomeone_picking", O_CREAT, S_IRWXU, 1);
	return (0);
}

void	destroy_sem(t_info info)
{
	sem_close(info.forks);
	sem_close(info.write);
	sem_close(info.someone_picking);
	sem_unlink("/sforks");
	sem_unlink("/swrite");
	sem_unlink("/ssomeone_picking");
}

void	free_all_malloc(t_info *info, t_phil **phils)
{
	int		i;

	i = -1;
	while (++i < info->num_phil)
		free(phils[i]);
	free(phils);
}

int		main(int ac, char **av)
{
	t_info		info;
	t_phil		**phils;
	int			i;

	if (ac < 5 || ac > 6)
		return (errormess("error: wrong number of arguments"));
	if (get_info(&info, ac, av))
		return (errormess("error: arguments"));
	if (!(phils = start_program(&info)))
		return (errormess("error: fatal"));
	while (!info.someone_is_dead &&
		info.phils_whos_eaten_enough < info.num_phil)
		usleep(100);
	i = -1;
	while (++i < info.num_phil)
	{
		sem_post(info.forks);
		pthread_join(phils[i]->thread, NULL);
	}
	destroy_sem(info);
	free_all_malloc(&info, phils);
	return (0);
}
