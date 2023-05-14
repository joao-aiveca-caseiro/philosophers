/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:27:56 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/14 13:07:11 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo, char c)
{
	size_t	time;

	pthread_mutex_lock(&philo->init->print_lock);
	time = get_time_ms() - philo->start_time;
	if (philo->init->completed < philo->init->philos_n
		&& !philo->init->death_flag)
	{
		if (c == 'f')
			printf("%ld %i has taken a fork\n", time, philo->id);
		else if (c == 'e')
			printf("%ld %i is eating\n", time, philo->id);
		else if (c == 's')
			printf("%ld %i is sleeping\n", time, philo->id);
		else if (c == 't')
			printf("%ld %i is thinking\n", time, philo->id);
	}
	if (c == 'a')
		printf("%ld all philosophers have eaten the required %i meals!\n",
			time, philo->init->min_meals);
	pthread_mutex_unlock(&philo->init->print_lock);
}
