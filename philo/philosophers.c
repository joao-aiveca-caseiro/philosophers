/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:36:55 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/08 18:41:58 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_forks(t_list *init)
{
	int	i;

	i = -1;
	init->forks = NULL;
	init->forks = malloc(sizeof(pthread_mutex_t) * init->philos_n);
	if (!init->forks)
		return (0);
	while (++i < init->philos_n)
	{
		if (pthread_mutex_init(&init->forks[i], NULL) != 0)
			return (0);
		printf("Fork %i successfully created!\n", i);
	}
	return (1);
}

int	init_util_mutexes(t_list *init)
{
	init->print_lock = NULL;
	init->print_lock = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(init->print_lock, NULL) != 0)
		return (0);
	return (1);
}

t_philo	*create_philosophers(t_list *init)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = NULL;
	philo = malloc(sizeof(t_philo) * init->philos_n);
	if (!philo)
		return (0);
	while (++i < init->philos_n)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &init->forks[i];
		philo[i].right_fork = &init->forks[(i + 1) % init->philos_n];
		philo[i].prev_meal_time = 0;
		philo[i].init = init;
		printf("PHILO ID: %i\n", philo[i].id);
		printf("LEFT FORK: %i\n", i);
		printf("RIGHT FORK: %i\n", (i + 1) % init->philos_n);
		printf("TIME: %zu\n\n", philo[i].prev_meal_time);
	}
	return (philo);
}

int	parsing_args(int argc, char **argv, t_list *init)
{
	init->philos_n = ft_atoi(argv[1]);
	init->time_to_die = ft_atoi(argv[2]);
	init->time_to_eat = ft_atoi(argv[3]);
	init->time_to_sleep = ft_atoi(argv[4]);
	printf("number of philos: %i\n", init->philos_n);
	printf("time to die: %i\n", init->time_to_die);
	printf("time to eat: %i\n", init->time_to_eat);
	printf("time_to_sleep: %i\n", init->time_to_sleep);
	if (init->philos_n <= 0 || init->time_to_die <= 0
		|| init->time_to_eat <= 0 || init->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		init->min_meals = ft_atoi(argv[5]);
		printf("minimum meals: %i\n", init->min_meals);
		if (init->min_meals <= 0)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	init;
	t_philo	*philo;

	init.philos_n = 0;
	init.time_to_die = 0;
	init.time_to_eat = 0;
	init.time_to_sleep = 0;
	init.min_meals = 0;
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: Invalid number of arguments.\n", 37);
		return (1);
	}
	if (parsing_args(argc, argv, &init) == 1)
	{
		write(2, "Error: Invalid argument.\n", 26);
		return (1);
	}
	create_forks(&init);
	init_util_mutexes(&init);
	philo = create_philosophers(&init);
	init_routine(philo, &init);
	return (0);
}
