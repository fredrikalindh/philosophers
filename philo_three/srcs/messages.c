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

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		++i;
	return i;
}

void ft_putnbr(uint64_t time)
{
	int index = 300;
	char time_string[300];
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
	write(1, &time_string[index], 300 - index);
}

int		errormess(char *mess)
{
	write(2, mess, ft_strlen(mess));
	write(2, "\n", 1);
	return (1);
}

int		message(int name, char *message)
{
	sem_wait(g_write);
	ft_putnbr(get_time(0));
	ft_putnbr(name);
	write(1, message, ft_strlen(message));
	sem_post(g_write);
	return (0);
}
