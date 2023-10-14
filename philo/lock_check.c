/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 00:43:37 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/14 08:28:46 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forced_check(t_philo *philosophers)
{
	if (philosophers->info->meals == 0)
		return (-1);
	if (philosophers->info->n_of_philos == 1)
	{
		printf("0 1 is thinking\n");
		printf("0 1 is has taken right fork\n");
		return (-1);
	}
	return (1);
}

void	lock_left(pthread_mutex_t *fork, t_philo *philosophers)
{
		pthread_mutex_lock(fork);
		philosophers->left = 1;
		check_and_print(philosophers, "has taken a fork");
}

int	lock_right(pthread_mutex_t *fork, t_philo *philosophers)
{
	if (philosophers->left == 1)
	{
		pthread_mutex_lock(fork);
		philosophers->right = 1;
		check_and_print(philosophers, "has taken a fork");
		return(1);
	}
	return(0);
}

void	unlock_left(pthread_mutex_t *fork, t_philo *philosophers)
{
	pthread_mutex_unlock(fork);
	philosophers->left = 0;
}

void	unlock_right(pthread_mutex_t *fork, t_philo *philosophers)
{
	pthread_mutex_unlock(fork);
	philosophers->right = 0;
}
