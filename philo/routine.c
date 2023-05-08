/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:17:51 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/08 19:01:43 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo, char c)
{
	size_t	time;

	pthread_mutex_lock(philo->init->print_lock);
	time = get_time_ms() - philo->start_time;
	if (c == 'f')
		printf("%ld %i has taken a fork\n", time, philo->id);
	else if (c == 'e')
		printf("%ld %i is eating\n", time, philo->id);
	else if (c == 's')
		printf("%ld %i is sleeping\n", time, philo->id);
	else if (c == 't')
		printf("%ld %i is thinking\n", time, philo->id);
	pthread_mutex_unlock(philo->init->print_lock);
}

void	init_routine(t_philo *philo, t_list *init)
{
	int	i;

	i = -1;
	while (++i < init->philos_n)
	{
		philo[i].start_time = get_time_ms();
	//	printf("PHILO %i START TIME: %i\n", i, philo[i].start_time);
		pthread_create(&philo[i].thread, NULL, routine_exec, &philo[i]);
		ft_usleep(100);
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
	print_state(philo, 'f');
	print_state(philo, 'f');
	print_state(philo, 'e');
	philo->prev_meal_time = get_time_ms();
	ft_usleep(philo->init->time_to_eat * 1000);
	philo->meal_count++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_state(philo, 's');
	ft_usleep(philo->init->time_to_sleep * 1000);
}

void	*routine_exec(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		print_state(philo, 't');
		ft_usleep(100);
	}
	return (0);
}
