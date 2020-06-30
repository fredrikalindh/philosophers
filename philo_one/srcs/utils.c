/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:25:54 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/27 12:25:49 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

unsigned long long	get_time(void)
{
	static struct timeval	start = {0, 0};
	struct timeval			tv;

	if (!start.tv_sec)
		gettimeofday(&start, NULL);
	gettimeofday(&tv, NULL);
	return (((tv.tv_sec - start.tv_sec) * (unsigned long long)1000) +
			((tv.tv_usec - start.tv_usec) / 1000));
}

void	real_sleep(u_int64_t n)
{
	u_int64_t start;

	start = get_time();
	while (get_time() - start < n)
		usleep(1000);
}