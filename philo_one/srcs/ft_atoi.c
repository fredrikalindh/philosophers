/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:21:39 by frlindh           #+#    #+#             */
/*   Updated: 2020/11/04 11:16:02 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi(const char *str)
{
	int i;
	int c;
	int neg;

	i = 0;
	c = 0;
	neg = 1;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t' ||
		str[i] == '\v' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((INT_MAX - (str[i] - '0')) / 10 < c)
			return (-1);
		c = c * 10 + str[i] - '0';
		i++;
	}
	return (!i || str[i]) ? (-1) : (c * neg);
}
