/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 00:44:08 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/11 00:44:08 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(t_info *info, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return (-1);
	info->n_of_philos = ft_atoi(argv[1]);
	if (info->n_of_philos < 1)
		return (-1);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->meals = ft_atoi(argv[5]);
	else
		info->meals = -1;
	if (info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0 || info->n_of_philos < 1)
		return (-1);
	info->finished_eating = 0;
	info->err = 0;
	info->is_dead = 0;
	return (0);
}

int	init_struct(t_philo **philosophers, t_info *info)
{
	*philosophers = NULL;
	*philosophers = malloc(sizeof(t_philo) * info->n_of_philos);
	if (!*philosophers)
		return (-1);
	(*philosophers)->info = info;
	return (0);
}

int	init_mutexes(pthread_mutex_t *m1, pthread_mutex_t *m2)
{
	if (pthread_mutex_init(m1, NULL))
		return (-1);
	if (pthread_mutex_init(m2, NULL))
		return (pthread_mutex_destroy(m2), -1);
	return (0);
}

int init_threads(t_philo *philosophers) {
    int i;

    // First loop: Initialize mutexes and set up philosopher structures
    for (i = 0; i < philosophers->info->n_of_philos; i++) {
        philosophers[i].id = i + 1;
        philosophers[i].primo_philo = philosophers;
        philosophers[i].n_meals = 0;
        philosophers[i].info = philosophers->info;
        philosophers[i].left = 0;
        philosophers[i].right = 0;

        if (pthread_mutex_init(&philosophers[i].posate_mutex, NULL) != 0 ||
            pthread_mutex_init(&philosophers[i].timing_mutex, NULL) != 0 ||
            pthread_mutex_init(&philosophers[i].death_timing, NULL) != 0) {
            return err(philosophers);
        }
    }

    // Second loop: Start threads
    for (i = 0; i < philosophers->info->n_of_philos; i++) {
        if (pthread_create(&philosophers[i].philo, NULL, philo_routine, &philosophers[i]) != 0) {
            return err(philosophers);
        }
    }

    return 0;
}
