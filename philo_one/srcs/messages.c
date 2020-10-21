/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:25:17 by fredrika          #+#    #+#             */
/*   Updated: 2020/10/21 16:27:58 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		++i;
	return (i);
}

void	ft_putnbr(uint64_t time)
{
	int		index;
	char	time_string[100];

	index = 100;
	time_string[--index] = ' ';
	if (!time)
	{
		write(1, "0 ", 2);
		return ;
	}
	while (time)
	{
		time_string[--index] = (time % 10) + '0';
		time /= 10;
	}
	write(1, &time_string[index], 100 - index);
}

int		errormess(char *mess)
{
	write(2, mess, ft_strlen(mess));
	write(2, "\n", 1);
	return (1);
}

int		message(t_phil *phil, char *message)
{
	pthread_mutex_lock(&phil->info->write);
	if (!phil->info->someone_is_dead)
	{
		ft_putnbr(get_time());
		ft_putnbr(phil->name);
		write(1, message, ft_strlen(message));
	}
	pthread_mutex_unlock(&phil->info->write);
	return (0);
}
