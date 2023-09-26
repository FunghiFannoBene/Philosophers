/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 04:16:47 by shhuang           #+#    #+#             */
/*   Updated: 2023/09/21 04:16:47 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
	t_philo *philosophers = arg;
	pthread_mutex_lock(&philosophers->posate);
	printf("sono: filosofo : %d\n", philosophers->id);
	pthread_mutex_unlock(&philosophers->posate);
}

int err(t_philo *philosophers)
{
	philosophers->info->err = 1;
	return(1);
}

static int init(t_philo *philosophers)
{
	int i=0;
	while(i < philosophers->info->n_of_philos)
	{
		philosophers[i].id = i+1;
		philosophers[i].primo_philo = philosophers;
		philosophers[i].info = philosophers->info;
		if (pthread_mutex_init(&philosophers[i].posate, NULL) || pthread_mutex_init(&philosophers[i].timing_mutex, NULL) || pthread_create(&philosophers[i].philo, NULL, philo_routine, &philosophers[i]))
			return (err(philosophers));
		sleep(1);
		i++;
	}
	i=0;
	while(i < philosophers->info->n_of_philos)
	{
		pthread_join(philosophers[i].philo, NULL);
		i++;
	}
}

static int	init_mutexes(pthread_mutex_t *m1, pthread_mutex_t *m2, pthread_mutex_t *m3)
{
	if (pthread_mutex_init(m1, NULL))
		return (-1);
	if (pthread_mutex_init(m2, NULL))
		return (pthread_mutex_destroy(m2), -1);
	if (pthread_mutex_init(m3, NULL))
		return (pthread_mutex_destroy(m2), pthread_mutex_destroy(m3), -1);
	return (0);
}

static int init_info(t_info *info, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return(-1);
	info->n_of_philos = ft_atoi(argv[1]);
	if(info->n_of_philos < 1)
		return(-1);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		info->meals = ft_atoi(argv[5]);
	else
		info->meals = 0;
	info->finished_eating = 0;
	info->err = 0;
	info->is_dead = 0;
}

int main(int argc, char** argv)
{
	t_philo *philosophers;
	t_info info;

	init_info(&info, argv, argc);
	philosophers = malloc(sizeof(t_philo) * info.n_of_philos);
	philosophers->info = &info;
	if(init_mutexes(&info.start, &info.end, &info.finish_eat) == -1)
		return(free(philosophers), 0);
	init(philosophers);
}