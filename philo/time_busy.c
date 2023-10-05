#include "philo.h"

void wait_to_eat(t_philo *philosophers)
{
	printf("%lld %d is thinking\n", philosophers->philo_s_time, philosophers->id);
	usleep(philosophers->info->time_to_eat * 1000);
}


int sleep_and_check(long long int eat, t_philo *philosophers)
{
	get_new_start(philosophers);
	long long int eat_time = philosophers->philo_s_time + eat;
	int i=0;
	while(!philosophers->info->is_dead && philosophers->philo_s_time < eat_time)
	{
		pthread_mutex_lock(&philosophers->info->end_mutex);
		if (philosophers->info->is_dead != 0)
		{
			pthread_mutex_unlock(&philosophers->info->end_mutex);
			return -1;
		}
		i++;
		pthread_mutex_unlock(&philosophers->info->end_mutex);
		usleep(300);
		get_new_start(philosophers);
	}
	return(0);
}