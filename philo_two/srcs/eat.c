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
	while (phil->info->n_forks < 2 && !phil->info->someone_is_dead)
		;
	sem_wait(phil->info->write);
	phil->info->n_forks -= 2;
	sem_post(phil->info->write);
	sem_wait(phil->info->forks);
	message(phil, FORK);
	sem_wait(phil->info->forks);
	if (!phil->info->someone_is_dead)
	{
		sem_wait(phil->eating);
		message(phil, FORK);
		message(phil, EAT);
		phil->last_eat = get_time();
		real_sleep(phil->info->time_to_eat);
		sem_wait(phil->info->write);
		phil->info->n_forks += 2;
		sem_post(phil->info->write);
		phil->times_eaten++;
	}
	sem_post(phil->info->forks);
	sem_post(phil->info->forks);
	sem_post(phil->eating);
}
