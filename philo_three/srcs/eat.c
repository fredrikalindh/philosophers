/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 15:35:48 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/27 13:56:50 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat(t_phil *phil)
{
	sem_wait(g_someone_picking);
	sem_wait(g_forks);
	message(phil->name, FORK);
	sem_wait(g_forks);
	sem_post(g_someone_picking);
	sem_wait(phil->eating);
	message(phil->name, FORK);
	message(phil->name, EAT);
	phil->last_eat = get_time(0);
	real_sleep(phil->info.time_to_eat);
	sem_post(g_forks);
	sem_post(g_forks);
	phil->times_eaten++;
	sem_post(phil->eating);
}
