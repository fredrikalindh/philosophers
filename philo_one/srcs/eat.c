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
	pthread_mutex_t		*t1 = &phil->info->forks[phil->name - 1];
	pthread_mutex_t		*t2 = &phil->info->forks[phil->name % phil->info->num_phil];
	pthread_mutex_lock(t1);
	message(phil, FORK);
	pthread_mutex_lock(t2);
	if (phil->info->someone_is_dead)
	{
		pthread_mutex_unlock(&phil->info->forks[phil->name - 1]);
		pthread_mutex_unlock(
			&phil->info->forks[phil->name % phil->info->num_phil]);
		return ;
	}
	phil->is_eating = 1;
	message(phil, FORK);
	message(phil, EAT);
	phil->last_eat = get_time();
	usleep(1000 * phil->info->time_to_eat);
	pthread_mutex_unlock(t1);
	pthread_mutex_unlock(t2);
	++phil->times_eaten;
	phil->is_eating = 0;
}
