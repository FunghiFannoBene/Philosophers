/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 01:30:42 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/11 01:30:42 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_dead(t_philo	*philosophers, int i)
{
	pthread_mutex_lock(&philosophers->info->death_mutex);
	philosophers->info->is_dead = 1;
	pthread_mutex_unlock(&philosophers->info->death_mutex);
	check_and_print_death(philosophers->primo_philo + i, "has died");
}

void	*monitor(void *arg)
{
	t_philo	*philosophers;
	int		i;

	i = 0;
	philosophers = (t_philo *)arg;
	usleep(philosophers->info->n_of_philos * 1000);
	if(philosophers->info->meals == 0)
		return(NULL);
	while (1)
	{
		pthread_mutex_lock(&philosophers->primo_philo[i].timing_mutex);
		get_new_start(&philosophers->primo_philo[i]);
		if (philosophers->primo_philo[i].philo_s_time
			>= (philosophers->primo_philo[i].philo_d_time))
		{
			pthread_mutex_unlock(&philosophers->primo_philo[i].timing_mutex);
			is_dead(philosophers, i);
			break ;
		}
		else
			pthread_mutex_unlock(&philosophers->primo_philo[i].timing_mutex);
		pthread_mutex_lock(&philosophers->info->finish_eat_mutex);
		if (philosophers->info->finished_eating == philosophers->info->n_of_philos)
			break ;
		pthread_mutex_unlock(&philosophers->info->finish_eat_mutex);

		i++;
		if (i == philosophers->info->n_of_philos)
			i = 0;
	}
	return (NULL);
}
