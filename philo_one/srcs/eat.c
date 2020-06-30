/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 15:35:48 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/27 14:07:59 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat(t_phil *phil)
{
	pthread_mutex_lock(phil->f1);
	message(phil, FORK);
	pthread_mutex_lock(phil->f2);
	if (phil->info->someone_is_dead)
	{
		pthread_mutex_unlock(phil->f1);
		pthread_mutex_unlock(phil->f2);
		return ;
	}
	phil->is_eating = 1;
	message(phil, FORK);
	message(phil, EAT);
	phil->last_eat = get_time();
	real_sleep(phil->info->time_to_eat);
	pthread_mutex_unlock(phil->f1);
	pthread_mutex_unlock(phil->f2);
	++phil->times_eaten;
	phil->is_eating = 0;
}
