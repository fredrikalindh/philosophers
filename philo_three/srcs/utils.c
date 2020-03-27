/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:25:54 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/24 16:50:53 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

uint64_t get_time(void)
{
	static struct timeval	start = {0,0};
	struct timeval	tv;

	if (!start.tv_sec)
		gettimeofday(&start, NULL);
	gettimeofday(&tv, NULL);
	return (((tv.tv_sec - start.tv_sec) * (uint64_t)1000) +
	((tv.tv_usec - start.tv_usec) / 1000));
}
