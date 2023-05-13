/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:17:51 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/13 15:07:30 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo, char c)
{
	size_t	time;

	pthread_mutex_lock(&philo->init->print_lock);
	time = get_time_ms() - philo->start_time;
	if (philo->init->completed < philo->init->philos_n && !philo->init->death_flag)
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

void	init_routine(t_philo *philo, t_list *init)
{
	int	i;

	i = -1;
	while (++i < init->philos_n)
	{
		philo[i].start_time = get_time_ms();
		pthread_create(&philo[i].thread, NULL, routine_exec, &philo[i]);
		ft_usleep(100);
	}
	i = -1;
	create_supervisor(philo);
	while (++i < init->philos_n)
	{
		if (pthread_join(philo[i].thread, NULL))
			return ;
		printf("BYE %i\n", i);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->can_die);
	print_state(philo, 'f');
	print_state(philo, 'f');
	print_state(philo, 'e');
	philo->prev_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->can_die);
	ft_usleep(philo->init->time_to_eat * 1000);
	// pthread_mutex_lock(&philo->init->print_lock);
	philo->meal_count++;
	// pthread_mutex_unlock(&philo->init->print_lock);
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
	while (philo->init->completed < philo->init->philos_n 
		&& !philo->init->death_flag)
	{
		eating(philo);
		sleeping(philo);
		print_state(philo, 't');
		ft_usleep(100);
	}
	return (NULL);
}
