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

void eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->info->forks[phil->name - 1]);
	message(phil, FORK);
	pthread_mutex_lock(&phil->info->forks[phil->name % phil->info->num_phil]);
	if (phil->info->someone_is_dead)
	{
		pthread_mutex_unlock(&phil->info->forks[phil->name - 1]);
		pthread_mutex_unlock(&phil->info->forks[phil->name % phil->info->num_phil]);
		return ;
	}
	phil->is_eating = 1;
	message(phil, FORK);
	message(phil, EAT);
	usleep(1000 * phil->info->time_to_eat);
	pthread_mutex_unlock(&phil->info->forks[phil->name - 1]);
	pthread_mutex_unlock(&phil->info->forks[phil->name % phil->info->num_phil]);
	phil->times_eaten++;
	phil->last_eat = get_time();
	phil->is_eating = 0;
}
