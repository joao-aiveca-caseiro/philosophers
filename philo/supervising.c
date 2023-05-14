/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervising.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:18:58 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/14 13:39:23 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*dying(t_philo *philo, int i)
{
	size_t	time;

	philo->init->death_flag = 1;
	time = get_time_ms() - philo->start_time;
	pthread_mutex_lock(&philo->init->print_lock);
	printf("%ld %i died\n", time, philo[i].id);
	pthread_mutex_unlock(&philo->init->print_lock);
	pthread_mutex_unlock(&philo[i].can_die);
	return (NULL);
}

void	philo_reached_goal(t_philo *philo, int i)
{
	philo->init->completed++;
	philo[i].full_flag = 1;
}

void	*supervising(void *philo_void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_void;
	while (philo->init->completed < philo->init->philos_n)
	{
		i = -1;
		while (++i < philo->init->philos_n)
		{
			pthread_mutex_lock(&philo[i].can_die);
			if (get_time_ms() - philo[i].prev_meal_time
				> (size_t)philo[i].init->time_to_die)
				return (dying(philo, i));
			pthread_mutex_unlock(&philo[i].can_die);
			pthread_mutex_lock(&philo->init->print_lock);
			if (philo[i].meal_count && philo[i].meal_count
				== philo->init->min_meals && philo[i].full_flag == 0)
				philo_reached_goal(philo, i);
			pthread_mutex_unlock(&philo->init->print_lock);
		}
	}
	print_state(philo, 'a');
	return (NULL);
}

int	create_supervisor(t_philo *philo)
{
	pthread_t	supervisor;

	if (pthread_create(&supervisor, NULL, &supervising, (void *)philo))
		return (0);
	if (pthread_join(supervisor, NULL))
		return (0);
	return (1);
}
