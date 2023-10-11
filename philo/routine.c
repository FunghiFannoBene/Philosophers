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
	if (philosophers->id % 2)
		usleep(philosophers->info->time_to_eat * 900);
	pthread_mutex_unlock(&philosophers->timing_mutex);
}

int	start_eat(t_philo *philosophers, pthread_mutex_t *left,
		pthread_mutex_t *right)
{
	pthread_mutex_lock(&philosophers->info->print_mutex);
	check_and_print(philosophers, "is eating");
	pthread_mutex_unlock(&philosophers->info->print_mutex);
	pthread_mutex_lock(&philosophers->info->finish_eat_mutex);
	get_new_time(philosophers);
	pthread_mutex_unlock(&philosophers->info->finish_eat_mutex);
	usleep(philosophers->info->time_to_eat * 1000);
	pthread_mutex_lock(&philosophers->info->finish_eat_mutex);
	philosophers->n_meals++;
	pthread_mutex_unlock(&philosophers->info->finish_eat_mutex);
	unlock_left(left, philosophers);
	unlock_right(right, philosophers);
	if (philosophers->n_meals == philosophers->info->meals
		|| philosophers->info->is_dead)
	{
		philosophers->info->finished_eating++;
		return (-1);
	}
	return (1);
}

static void	good_night(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->info->print_mutex);
	check_and_print(philosophers, "is sleeping");
	pthread_mutex_unlock(&philosophers->info->print_mutex);
	usleep(philosophers->info->time_to_sleep * 1000);
}

static void	think(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->info->print_mutex);
	check_and_print(philosophers, "is thinking");
	pthread_mutex_unlock(&philosophers->info->print_mutex);
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
	while (!philosophers->info->is_dead)
	{
		lock_left(left_fork, philosophers);
		lock_right(right_fork, philosophers);
		if (philosophers->left && philosophers->right)
		{
			if (start_eat(philosophers, left_fork, right_fork) == -1)
				return (NULL);
			good_night(philosophers);
			think(philosophers);
		}
	}
	return (NULL);
}
