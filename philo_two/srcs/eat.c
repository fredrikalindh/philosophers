/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 15:35:48 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/25 15:08:45 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat(t_phil *phil)
{
	sem_wait(phil->info->someone_picking);
	sem_wait(phil->info->forks);
	message(phil, FORK);
	sem_wait(phil->info->forks);
	sem_post(phil->info->someone_picking);
	if (!phil->info->someone_is_dead)
	{
		sem_wait(phil->eating);
		message(phil, FORK);
		message(phil, EAT);
		phil->last_eat = get_time();
		real_sleep(phil->info->time_to_eat);
		phil->times_eaten++;
	}
	sem_post(phil->eating);
	sem_post(phil->info->forks);
	sem_post(phil->info->forks);
}