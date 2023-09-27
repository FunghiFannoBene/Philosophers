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

void ft_sleep(long long int time)
{
	usleep(time * 1000);
}

long long int ms_true(t_philo *philosophers)
{
	return(get_time_in_milliseconds() - philosophers->info->start_time);
}

void *monitor(void *arg)
{
	t_philo *philosophers;

	philosophers = (t_philo *) arg;
	philosophers->id_iterator = 0;
	while(philosophers->info->is_dead)
	{
		if((ms_true(philosophers) - philosophers[philosophers->id_iterator].philo_s_time) >= (long long int)philosophers->info->time_to_die && philosophers->info->is_dead)
		{
			if(philosophers->info->is_dead)
			{
			}
			return(philosophers->info->is_dead = 0, &philosophers->id_iterator);
		}
		else
		{
		philosophers->id_iterator++;
		if(philosophers->id_iterator == philosophers->info->n_of_philos)
			philosophers->id_iterator = 0;
		}
	}
	return(NULL);
}

long long get_time_in_milliseconds(void) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    
    long long milliseconds = (long long)current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    
    return milliseconds;
}

void *philo_routine(void *arg)
{
	t_philo *philosophers;
	pthread_t monitor_t;
	int *dead;


	dead = malloc(sizeof(int) * 1);
	philosophers = (t_philo *) arg;
	if(philosophers->info->flag == 0)
	{
		philosophers->philo_s_time = get_time_in_milliseconds() - philosophers->info->start_time;
		pthread_create(&monitor_t, NULL, monitor, philosophers);
		pthread_join(monitor_t, (void **)&dead);
		philosophers->info->flag++;
	}
	while(philosophers->info->is_dead)
	{
		
	}
	if(1 == philosophers->info->flag++)
		printf("%lld %d has died.\n", ms_true(philosophers), *dead+1);
	return(NULL);
}

int err(t_philo *philosophers)
{
	philosophers->info->err = 1;
	return(1);
}

static int init(t_philo *philosophers)
{
	int i=0;
	if(philosophers->info->start_time == 0)
		philosophers->info->start_time = get_time_in_milliseconds();
	while(i < philosophers->info->n_of_philos)
	{
		philosophers[i].id = i+1;
		philosophers[i].primo_philo = philosophers;
		philosophers[i].info = philosophers->info;
		if (pthread_mutex_init(&philosophers[i].posate, NULL) || pthread_mutex_init(&philosophers[i].timing_mutex, NULL) || pthread_create(&philosophers[i].philo, NULL, philo_routine, &philosophers[i]))
			return (err(philosophers));
		i++;
	}
	return(0);
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
	info->is_dead = 1;
	info->start_time = 0;
	info->flag = 0;
	return(0);
}

int main(int argc, char** argv)
{
	t_philo *philosophers;
	t_info info;

	int i = 0;

	if(init_info(&info, argv, argc) == -1)
		return(printf("Args errati...\n"));
	philosophers = malloc(sizeof(t_philo) * info.n_of_philos);
	philosophers->info = &info;
	if(init_mutexes(&info.start, &info.end, &info.finish_eat) == -1)
		return(free(philosophers), 0);
	init(philosophers);
	while(i < philosophers->info->n_of_philos)
	{
		pthread_join(philosophers[i].philo, NULL);
		i++;
	}
}
