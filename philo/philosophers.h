/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:32 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/01 04:40:20 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>

typedef struct s_philo
{
	int	philos_n;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_meals;
}	t_philo;

int	ft_atoi(const char *str);
int	parsing_args(int argc, char **argv, t_philo *philo);

#endif
