/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:25:17 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/25 16:51:39 by fredrikalindh    ###   ########.fr       */
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
	sem_wait(phil->info.write);
	ft_printf("%d philosopher %d ", get_time(), phil->name);
	if (type == FORK)
		ft_printf("has taken a fork\n");
	else if (type == EAT)
		ft_printf("is eating\n");
	else if (type == SLEEP)
		ft_printf("is sleeping\n");
	else if (type == THINK)
		ft_printf("is thinking\n");
	else if (type == ENOUGH)
		ft_printf("has eaten enough\n");
	else if (type == DEAD)
		ft_printf("died\n");
	sem_post(phil->info.write);
	return (0);
}
