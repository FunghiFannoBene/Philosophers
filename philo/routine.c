/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:51:14 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/16 22:51:14 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	good_night(t_philo *philosophers)
{
	int	sleep;

	sleep = philosophers->info->time_to_sleep * 1000;
	check_and_print(philosophers, "is sleeping");
	usleep(sleep);
}

static void	think(t_philo *philosophers)
{
	int	crea_cerchio_perfetto;

	check_and_print(philosophers, "is thinking");
	if (philosophers->info->n_of_philos % 2)
	{
		crea_cerchio_perfetto = 0;
		if (philosophers->info->time_to_sleep
			<= (philosophers->info->time_to_eat
				* 2))
		{
			crea_cerchio_perfetto = (philosophers->info->time_to_eat * 2
					- philosophers->info->time_to_sleep) * 1000;
		}
		usleep(crea_cerchio_perfetto);
	}
}

static void	determine_fork_order(t_philo *philosophers,
		pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &philosophers->posate_mutex;
	right_fork = &(philosophers->primo_philo[(philosophers->id
				% philosophers->info->n_of_philos)].posate_mutex);
	if (left_fork < right_fork)
	{
		*first_fork = left_fork;
		*second_fork = right_fork;
	}
	else
	{
		*first_fork = right_fork;
		*second_fork = left_fork;
	}
}

static int	is_philo_dead(t_philo *philosophers)
{
	int	is_dead;

	pthread_mutex_lock(&philosophers->info->death_mutex);
	is_dead = philosophers->info->is_dead;
	pthread_mutex_unlock(&philosophers->info->death_mutex);
	return (is_dead);
}

void	*philo_routine(void *arg)
{
	t_philo			*philosophers;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	philosophers = (t_philo *)arg;
	determine_fork_order(philosophers, &first_fork, &second_fork);
	init_time(philosophers);
	if (forced_check(philosophers) == -1)
		return (NULL);
	while (1)
	{
		if (start_eat(philosophers, first_fork, second_fork) == -1)
			return (NULL);
		good_night(philosophers);
		think(philosophers);
		if (is_philo_dead(philosophers))
			break ;
	}
	return (NULL);
}
