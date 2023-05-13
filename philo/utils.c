/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 01:48:43 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/12 03:22:10 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time_ms(void)
{
	struct timeval	time;
	size_t			time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_ms);
}

void	ft_usleep(size_t time)
{
	size_t	start_time;

	start_time = get_time_ms();
	if (time < 10000)
		usleep(time);
	else
		while ((get_time_ms() - start_time) < time / 1000)
			usleep(time / 10000);
}

int	int_overflow(int res, char c, int sign)
{
	if (sign == 1)
		if (res == (INT_MAX - 7) && (c - 48) > 7)
			return (0);
	if (sign == -1)
		if (res == (INT_MAX - 7) && (c - 48) > 8)
			return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		if (res > INT_MAX / 10)
			return (0);
		res *= 10;
		if (!int_overflow(res, str[i], sign))
			return (0);
		res += str[i++] - 48;
	}
	return (res * sign);
}
