/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:17:51 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/14 13:40:16 by jaiveca-         ###   ########.fr       */
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
		if (pthread_create(&philo[i].thread, NULL, routine_exec, &philo[i]))
			return ;
		ft_usleep(100);
	}
	i = -1;
	if (!create_supervisor(philo))
		return ;
	while (++i < init->philos_n)
		if (pthread_join(philo[i].thread, NULL))
			return ;
}

void	eating(t_philo *philo)
{
	pthread_mutex_unlock(&philo->init->print_lock);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->can_die);
	print_state(philo, 'f');
	print_state(philo, 'f');
	print_state(philo, 'e');
	philo->prev_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->can_die);
	ft_usleep(philo->init->time_to_eat * 1000);
	pthread_mutex_lock(&philo->init->print_lock);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->init->print_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_state(philo, 's');
	ft_usleep(philo->init->time_to_sleep * 1000);
}

void	single_philo_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->can_die);
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, 'f');
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->can_die);
}

void	*routine_exec(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->init->philos_n == 1)
	{
		single_philo_case(philo);
		return (NULL);
	}
	pthread_mutex_lock(&philo->init->print_lock);
	while (philo->init->completed < philo->init->philos_n
		&& !philo->init->death_flag)
	{
		eating(philo);
		sleeping(philo);
		print_state(philo, 't');
		pthread_mutex_lock(&philo->init->print_lock);
		ft_usleep(100);
	}
	pthread_mutex_unlock(&philo->init->print_lock);
	return (NULL);
}
