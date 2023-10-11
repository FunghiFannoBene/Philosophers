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
	philosophers->info->is_dead = 1;
	pthread_mutex_lock(&philosophers->info->print_mutex);
	printf("%lld %d has died\n", philosophers->primo_philo[i].philo_s_time,
		philosophers->primo_philo[i].id);
	pthread_mutex_unlock(&philosophers->info->print_mutex);
}

void	*monitor(void *arg)
{
	t_philo	*philosophers;
	int		i;

	i = 0;
	philosophers = (t_philo *)arg;
	usleep(philosophers->info->n_of_philos * 1000);
	while (1)
	{
		get_new_start(&philosophers->primo_philo[i]);
		if (philosophers->info->finished_eating
			== philosophers->info->n_of_philos
			|| philosophers->info->meals == 0)
			break ;
		if (philosophers->primo_philo[i].philo_s_time
			>= (philosophers->primo_philo[i].philo_d_time))
		{
			is_dead(philosophers, i);
			break ;
		}
		i++;
		usleep(100);
		if (i == philosophers->info->n_of_philos)
			i = 0;
	}
	return (NULL);
}
