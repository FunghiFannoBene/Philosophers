#include "philo.h"

void *monitor(void *arg)
{
	t_philo *philosophers;
	int i;
	i=0;
	philosophers = (t_philo *)arg;
	usleep(philosophers->info->n_of_philos * 1000);
	while(1)
	{
		if(philosophers->info->meals == 0)
			return(NULL);
		get_new_start(&philosophers->primo_philo[i]);
		if(philosophers->info->finished_eating == philosophers->info->n_of_philos && philosophers->info->meals >= 0)
			break;
		if(philosophers->primo_philo[i].philo_s_time >= philosophers->primo_philo[i].philo_d_time)
		{
			philosophers->info->is_dead = 1;
			usleep(philosophers->info->n_of_philos * 100);
			printf("%lld %d has died.\n",philosophers->primo_philo[i].philo_s_time , philosophers->primo_philo[i].id);
			break;
		}
		i++;
		usleep(100);
		if (i == philosophers->info->n_of_philos)
   			 i = 0;
	}
	return(NULL);
}