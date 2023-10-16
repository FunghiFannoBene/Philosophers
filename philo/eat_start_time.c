/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_start_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:56:20 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/16 23:00:53 by shhuang          ###   ########.fr       */
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
	if (philosophers->id == philosophers->info->n_of_philos
		&& philosophers->info->n_of_philos % 2)
		usleep(philosophers->info->time_to_eat * 1000);
}

int	start_eat(t_philo *philosophers, pthread_mutex_t *left,
		pthread_mutex_t *right)
{
	lock_left(left, philosophers);
	lock_right(right, philosophers);
	check_and_print(philosophers, "is eating");
	pthread_mutex_lock(&philosophers->timing_mutex);
	get_new_time(philosophers);
	pthread_mutex_unlock(&philosophers->timing_mutex);
	usleep(philosophers->info->time_to_eat * 1000);
	unlock_left(left);
	unlock_right(right);
	philosophers->n_meals++;
	if (philosophers->n_meals == philosophers->info->meals)
	{
		pthread_mutex_lock(&philosophers->info->finish_eat_mutex);
		philosophers->info->finished_eating++;
		pthread_mutex_unlock(&philosophers->info->finish_eat_mutex);
		return (-1);
	}
	return (1);
}
