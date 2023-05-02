/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:36:55 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/01 04:47:55 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing_args(int argc, char **argv, t_philo *philo)
{
	philo->philos_n = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	printf("number of philos: %i\n", philo->philos_n);
	printf("time to die: %i\n", philo->time_to_die);
	printf("time to eat: %i\n", philo->time_to_eat);
	printf("time_to_sleep: %i\n", philo->time_to_sleep);
	if (philo->philos_n <= 0 || philo->time_to_die <= 0
		|| philo->time_to_eat <= 0 || philo->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		philo->min_meals = ft_atoi(argv[5]);
		printf("minimum meals: %i\n", philo->min_meals);
		if (philo->min_meals <= 0)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	philo.philos_n = 0;
	philo.time_to_die = 0;
	philo.time_to_eat = 0;
	philo.time_to_sleep = 0;
	philo.min_meals = 0;
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: Invalid number of arguments.\n", 37);
		return (1);
	}
	if (parsing_args(argc, argv, &philo) == 1)
	{
		write(2, "Error: Invalid argument.\n", 26);
		return (1);
	}
	return (0);
}
