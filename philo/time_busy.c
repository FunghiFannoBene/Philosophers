#include "philo.h"

void wait_to_eat(t_philo *philosophers)
{
	printf("%lld %d is thinking\n", philosophers->philo_s_time, philosophers->id);
	usleep(philosophers->info->time_to_eat * 1000);
}

int sleep_and_check(long long int eat, t_philo *philosophers)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	left_fork = &philosophers->posate_mutex;
	right_fork = &(philosophers->primo_philo[(philosophers->id % philosophers->info->n_of_philos)].posate_mutex);
	get_new_start(philosophers);
	long long int eat_time = philosophers->philo_s_time + eat;
	int i=0;
	while(!philosophers->info->is_dead && philosophers->philo_s_time < eat_time)
	{
		if (philosophers->info->is_dead != 0)
		{
			pthread_mutex_unlock(right_fork);
			pthread_mutex_unlock(left_fork);
			return -1;
		}
		i++;
		usleep(300);
		get_new_start(philosophers);
	}
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
	return(0);
}

int sleep_and_check2(long long int eat, t_philo *philosophers)
{
	get_new_start(philosophers);
	long long int eat_time = philosophers->philo_s_time + eat;
	int i=0;
	while(!philosophers->info->is_dead && philosophers->philo_s_time < eat_time)
	{
		if (philosophers->info->is_dead != 0)
		{
			return -1;
		}
		i++;
		usleep(300);
		get_new_start(philosophers);
	}
	return(0);
}