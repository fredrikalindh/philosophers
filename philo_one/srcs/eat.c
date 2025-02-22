/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 15:35:48 by fredrika          #+#    #+#             */
/*   Updated: 2020/11/04 10:06:34 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat(t_phil *phil)
{
	if ((phil->name % 2) == 0)
		pthread_mutex_lock(phil->f1);
	pthread_mutex_lock(phil->f2);
	message(phil, FORK);
	if ((phil->name % 2) == 1)
		pthread_mutex_lock(phil->f1);
	if (!phil->info->someone_is_dead)
	{
		pthread_mutex_lock(&phil->is_eating);
		message(phil, FORK);
		message(phil, EAT);
		phil->last_eat = get_time();
		real_sleep(phil->info->time_to_eat);
		++phil->times_eaten;
		pthread_mutex_unlock(&phil->is_eating);
	}
	pthread_mutex_unlock(phil->f1);
	pthread_mutex_unlock(phil->f2);
}
