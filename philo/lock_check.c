/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 00:43:37 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/16 06:20:18 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forced_check(t_philo *philosophers)
{
	if (philosophers->info->meals == 0)
		return (-1);
	if (philosophers->info->n_of_philos == 1)
	{
		pthread_mutex_lock(&philosophers->posate_mutex);
		printf("0 %d has taken a fork\n", philosophers->id);
		printf("%d %d has died\n", philosophers->info->time_to_die, philosophers->id);
		pthread_mutex_unlock(&philosophers->posate_mutex);
		return (-1);
	}
	return (1);
}

void	lock_left(pthread_mutex_t *fork, t_philo *philosophers)
{
		pthread_mutex_lock(fork);
		check_and_print(philosophers, "has taken a fork");
}

int	lock_right(pthread_mutex_t *fork, t_philo *philosophers)
{
		pthread_mutex_lock(fork);
		check_and_print(philosophers, "has taken a fork");
		return(1);
}

void	unlock_left(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

void	unlock_right(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}
