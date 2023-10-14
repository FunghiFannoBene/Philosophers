/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 00:51:07 by shhuang           #+#    #+#             */
/*   Updated: 2023/09/11 00:51:07 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_time(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->timing_mutex);
	philosophers->philo_first_s_time = get_time_in_milliseconds();
	get_new_time(philosophers);
	pthread_mutex_unlock(&philosophers->timing_mutex);
	if (philosophers->id % 2)
		usleep(philosophers->info->time_to_eat * 1000);
}

int	start_eat(t_philo *philosophers, pthread_mutex_t *left,
		pthread_mutex_t *right)
{
	check_and_print(philosophers, "is eating");
	pthread_mutex_lock(&philosophers->timing_mutex);
	get_new_time(philosophers);
	pthread_mutex_unlock(&philosophers->timing_mutex);
	usleep(philosophers->info->time_to_eat * 1000);
	philosophers->n_meals++;
	unlock_left(left, philosophers);
	unlock_right(right, philosophers);
	if (philosophers->n_meals == philosophers->info->meals)
	{
		pthread_mutex_lock(&philosophers->info->finish_eat_mutex);
		philosophers->info->finished_eating++;
		pthread_mutex_unlock(&philosophers->info->finish_eat_mutex);
		return (-1);
	}
	return (1);
}

static void	good_night(t_philo *philosophers)
{
	check_and_print(philosophers, "is sleeping");
	usleep(philosophers->info->time_to_sleep * 1000);
}

static void	think(t_philo *philosophers)
{
	check_and_print(philosophers, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo			*philosophers;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	philosophers = (t_philo *)arg;
	left_fork = &philosophers->posate_mutex;
	right_fork = &(philosophers->primo_philo[(philosophers->id
				% philosophers->info->n_of_philos)].posate_mutex);
	init_time(philosophers);
	if (forced_check(philosophers) == -1)
		return (NULL);
	while (1)
	{
		if (philosophers->left == 0)
			lock_left(left_fork, philosophers);
		if(lock_right(right_fork, philosophers))
		{
			if (start_eat(philosophers, left_fork, right_fork) == -1)
				return (NULL);
			good_night(philosophers);
			think(philosophers);
		}
		pthread_mutex_lock(&philosophers->info->death_mutex);
		if(philosophers->info->is_dead)
		{
			pthread_mutex_unlock(&philosophers->info->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philosophers->info->death_mutex);
	}
	if(philosophers->left == 1)
		pthread_mutex_unlock(left_fork);	 
	if(philosophers->right == 1)
		pthread_mutex_unlock(right_fork);
	return (NULL);
}
