/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 15:35:48 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/25 16:51:37 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void eat(t_phil *phil)
{
	sem_wait(phil->info.forks);
	message(phil, FORK);
	sem_wait(phil->info.forks);
	phil->eating = 1;
	message(phil, FORK);
	message(phil, EAT);
	usleep(1000 * phil->info.time_to_eat);
	sem_post(phil->info.forks);
	sem_post(phil->info.forks);
	phil->times_eaten++;
	phil->last_eat = get_time();
	phil->eating = 0;
}
