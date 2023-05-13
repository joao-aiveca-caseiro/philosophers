/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervising.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:58 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/12 03:03:48 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*dying(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->init->print_lock);
	time = get_time_ms() - philo->start_time;
	// printf("%ld %i died 💀\n", time, philo->id);
	printf("%ld %i died\n", time, philo->id);
	pthread_mutex_unlock(&philo->init->print_lock);
	return (NULL);
}

void	*supervising(void *philo_void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_void;
	i = -1;
	while (1)
	{
		while (++i < philo->init->philos_n)
		{
			pthread_mutex_lock(&philo[i].can_die);
			if (get_time_ms() - philo[i].prev_meal_time
				> philo[i].init->time_to_die)
				return (dying(philo));
			pthread_mutex_unlock(&philo[i].can_die);
		}
		i = -1;
	}

}

void	create_supervisor(t_philo *philo)
{
	pthread_t	supervisor;

	if (!pthread_create(&supervisor, NULL, &supervising, (void *)philo))
		pthread_join(supervisor, NULL);
}
