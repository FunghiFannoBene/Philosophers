/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 00:43:37 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/11 00:48:51 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forced_check(t_philo *philosophers)
{
	if (philosophers->info->meals == 0)
		return (-1);
	if (philosophers->info->is_dead == 1)
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
	if (philosophers->left == 0)
	{
		pthread_mutex_lock(fork);
		philosophers->left = 1;
		pthread_mutex_lock(&(philosophers->info->print_mutex));
		check_and_print(philosophers, "has taken a fork");
		pthread_mutex_unlock(&(philosophers->info->print_mutex));
	}
}

void	lock_right(pthread_mutex_t *fork, t_philo *philosophers)
{
	if (philosophers->left == 1)
	{
		pthread_mutex_lock(fork);
		philosophers->right = 1;
		pthread_mutex_lock(&philosophers->info->print_mutex);
		check_and_print(philosophers, "has taken a fork");
		pthread_mutex_unlock(&philosophers->info->print_mutex);
	}
}

void	unlock_left(pthread_mutex_t *fork, t_philo *philosophers)
{
	philosophers->left = 0;
	pthread_mutex_unlock(fork);
}

void	unlock_right(pthread_mutex_t *fork, t_philo *philosophers)
{
	philosophers->right = 0;
	pthread_mutex_unlock(fork);
}