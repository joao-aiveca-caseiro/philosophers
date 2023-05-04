/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:17:51 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/04 19:10:12 by jaiveca-         ###   ########.fr       */
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

void	*routine_exec(void *init)
{
	printf("IN ROUTINE\n");
	(void) init;
	// eating(init);
	// sleeping(init);
	return (0);
}