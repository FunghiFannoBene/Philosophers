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
	if (philosophers->info->n_of_philos != 1)
		check_and_print_death(philosophers->primo_philo + i, "has died");
}

static int	check_eat(t_philo	*philosophers)
{
	pthread_mutex_lock(&philosophers->info->finish_eat_mutex);
	if (philosophers->info->finished_eating == philosophers->info->n_of_philos)
	{
		pthread_mutex_unlock(&philosophers->info->finish_eat_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philosophers->info->finish_eat_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_philo		*philosophers;
	int			i;

	i = 0;
	philosophers = (t_philo *)arg;
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
		pthread_mutex_unlock(&philosophers->primo_philo[i].timing_mutex);
		if (check_eat(philosophers) == -1)
			break ;
		i++;
		if (i == philosophers->info->n_of_philos)
			i = 0;
	}
	return (NULL);
}
