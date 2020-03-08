/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:02:16 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/08 22:10:38 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int		errormess(char *mess)
{
	ft_printf("%s\n", mess);
	return (1);
}

int	get_time(struct timeval start, struct timeval tv)
{
	return ((int)((tv.tv_sec - start.tv_sec) * 1000 + ((tv.tv_usec - start.tv_usec) * 000.1)));
}

int		gettimeofsim(int start)
{
	struct timeval	tv;
}

void	start_phil(void *phil)
{
	t_phil p;

	p = (t_phil *)phil;
	while (1)
		if (p->times_eaten == p->info.maxeat)
			break ;
		pthread_mutex_lock(p->l_fork);
		ft_printf("%d %d has taken a fork\n", gettimeofsim(p->info.start_program), p->name);
		pthread_mutex_lock(p->r_fork);
		ft_printf("%d %d has taken a fork\n", gettimeofsim(p->info.start_program), p->name);
		ft_printf("%d %d is eating\n", gettimeofsim(p->info.start_program), p->name);
		usleep(p->info.time_to_eat * 1000);
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		p->time_to_die = p->info.time_to_die;
		p->info.maxeat != -1 ? p->times_eaten++ : 0;
		ft_printf("%d %d is sleeping\n", gettimeofsim(p->info.start_program), p->name);
		usleep(p->info.time_to_sleep * 1000);
		ft_printf("%d %d is thinking\n", gettimeofsim(p->info.start_program), p->name);
	}
}

int		check_ttd(t_phil **phils, pthread_t **threads)
{
	int				i;
	int				max;
	struct timeval	tv;

	i = -1;
	max = phils[i]->info.num_phil;
	while (++i < max)
	{
		if (phils[i]->times_eaten == phils[i]->info.max_eat)
			continue ;
		else
		{
			gettimeofday(&tv, NULL);
			if ((tv->tv_sec * 1000 + tv->tv_usec * 000.1) -
			phils[i]->time_to_die >  phils[i]->info.time_to_die)
				break ;
		}
	}
	if (i == max)
		return (i);
	i = -1;
	while (threads[++i] < max)
		pthread_detach(threads[i]);
	ft_printf("%d %d died\n", get_time(tv, ), dead);
	return (-1);
}

int		start_program(t_info info)
{
	t_phil			**start;
	int				i;
	int				dead;
	pthread_mutex_t	*first;
	pthread_mutex_t	*curr;
	pthread_t		**threads;

	i = -1;
	pthread_mutex_init(curr);
	first = curr;
	threads = (pthread_t **)mmalloc(sizeof(pthread_t *) * info.num_phil); // malloc pthread_mutexes also ??
	start = (t_phil **)mmalloc(sizeof(t_phil *) * info.num_phil); // malloc pthread_mutexes also ??
	while (++i < info.num_phil)
	{
		start[i] = (s_phil *)mmalloc(sizeof(s_phil));
		start[i]->name = i;
		start[i]->l_fork = curr;
		(i + 1 < info.num_phil) ? pthread_mutex_init(curr) : curr = first;
		start[i]->r_fork = curr;
		start[i]->time_to_die = info.time_to_die;
		start[i]->times_eaten = 0;
		pthread_create(threads[i], NULL, start_phil, (void *)start[i]);
	}
	i = -1;
	while (check_ttd(start, threads)) >= 0)
		usleep(1000);
	while (++i < info.num_phil)
		pthread_join(threads[i], NULL);
	return (0);
}

int		 main(int ac, char *av[])
{
	t_info p;

	if (ac < 5 || ac > 6)
		return (errormess("wrong usage"));
	if (!(p.num_phil = ft_atoi(av[1])))
		return (errormess("bad instruction of number_of_philosophers"));
	if (!(p.time_to_die = ft_atoi(av[2])))
		return (errormess("bad instruction of time_to_die"));
	if (!(p.time_to_eat = ft_atoi(av[3])))
		return (errormess("bad instruction of time_to_eat"));
	if (!(p.time_to_sleep = ft_atoi(av[4])))
		return (errormess("bad instruction of time_to_sleep"));
	if (ac == 6 && !(p.max_eat = ft_atoi(av[5])))
		return (errormess("bad instruction of number_of_times_each_philosopher_must_eat"));
	else if (ac == 5)
		p.max_eat = -1;
	// return (start_program(p));
	return (0);
}
