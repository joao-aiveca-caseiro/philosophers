/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaiveca- <jaiveca-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:08:32 by jaiveca-          #+#    #+#             */
/*   Updated: 2023/05/13 14:15:39 by jaiveca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_list
{
	int				philos_n;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_meals;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	int				completed;
	int				death_flag;
}	t_list;

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	can_die;
	pthread_t		thread;
	int				id;
	size_t			prev_meal_time;
	size_t			start_time;
	int				meal_count;
	int				full_flag;
	t_list			*init;
}	t_philo;

int		ft_atoi(const char *str);
int		parsing_args(int argc, char **argv, t_list *init);
size_t	get_time_ms(void);
void	init_routine(t_philo *philo, t_list *init);
void	*routine_exec(void *init);
void	ft_usleep(size_t time);
void	create_supervisor(t_philo *philo);
void	print_state(t_philo *philo, char c);

#endif
