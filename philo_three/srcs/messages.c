/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:25:17 by fredrika          #+#    #+#             */
/*   Updated: 2020/04/15 23:09:38 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int		errormess(char *mess)
{
	ft_printf("%s\n", mess);
	return (1);
}

int		message(t_phil *phil, int type)
{
	sem_wait(g_write);
	sem_wait(g_dead);
	sem_post(g_dead);
	if (type == FORK)
		ft_printf("%d philosopher %d has taken a fork\n",
		get_time(), phil->name);
	else if (type == EAT)
		ft_printf("%d philosopher %d is eating\n",
		get_time(), phil->name);
	else if (type == SLEEP)
		ft_printf("%d philosopher %d is sleeping\n",
		get_time(), phil->name);
	else if (type == THINK)
		ft_printf("%d philosopher %d is thinking\n",
		get_time(), phil->name);
	else if (type == ENOUGH)
		ft_printf("%d philosopher %d has eaten enough\n",
		get_time(), phil->name);
	else if (type == DEAD)
		ft_printf("%d philosopher %d died\n",
		get_time(), phil->name);
	sem_post(g_write);
	return (0);
}
