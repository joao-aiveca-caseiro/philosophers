/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:17:51 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/08 13:16:33 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_routine(t_philo *philo, t_list *init)
{
	int	i;

	i = -1;
	while (++i < init->philos_n)
	{
		philo[i].start_time = get_time_ms();
		pthread_create(&philo[i].thread, NULL, routine_exec, &philo[i]);
		usleep(100);
	}
	i = -1;
	while (++i < init->philos_n)
	{
		pthread_join(philo[i].thread, NULL);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	printf("%llims %i has taken a fork\n", get_time_ms() - philo->start_time, philo->id);
	printf("%llims %i has taken a fork\n", get_time_ms() - philo->start_time, philo->id);
	printf("%llims %i is eating\n", get_time_ms() - philo->start_time, philo->id);
	usleep(philo->init->time_to_eat * 1000);
	philo->prev_meal_time = get_time_ms();
	philo->meal_count++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	printf("%llims %i is sleeping\n", get_time_ms() - philo->start_time, philo->id);
	usleep(philo->init->time_to_sleep * 1000);
}

void	*routine_exec(void *void_philo)
{
	t_philo	*philo;
	
	philo = (t_philo *)void_philo;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		printf("%llims %i is thinking\n", get_time_ms() - philo->start_time, philo->id);
//		usleep(100);
	}
	return (0);
}