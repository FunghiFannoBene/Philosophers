#include "philo.h"


void init_time(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->timing_mutex);
	philosophers->philo_first_s_time = get_time_in_milliseconds();
	get_new_time(philosophers);
	pthread_mutex_unlock(&philosophers->timing_mutex);
}


int	philo_print(t_philo *philosophers, char *message)
{
	if (philosophers->info->is_dead == 0)
	{
		get_new_start(philosophers);
		if (philosophers->info->is_dead == 0)
		{
			printf("%lld %d %s\n", philosophers->philo_s_time, philosophers->id, message);
			return (0);
		}
	}
	return (-1);
}

int start_eat(t_philo *philosophers)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	left_fork = &philosophers->posate_mutex;
	right_fork = &(philosophers->primo_philo[(philosophers->id % philosophers->info->n_of_philos)].posate_mutex);

	pthread_mutex_lock(left_fork);
	pthread_mutex_lock(right_fork);
	if (philo_print(philosophers, "has taken left fork") < 0 && philosophers->info->is_dead == 0)
		return (pthread_mutex_unlock(right_fork), pthread_mutex_unlock(left_fork), -1);
	if (philo_print(philosophers, "has taken right fork") < 0 && philosophers->info->is_dead == 0)
		return (pthread_mutex_unlock(right_fork) ,pthread_mutex_unlock(left_fork) , -1);
	get_new_time(philosophers);
	if (philo_print(philosophers, "is eating") < 0)
		return ( pthread_mutex_unlock(right_fork),pthread_mutex_unlock(left_fork), -1);
	sleep_and_check(philosophers->info->time_to_eat, philosophers);
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
	if(++philosophers->n_meals == philosophers->info->meals)
	{
		pthread_mutex_lock(&philosophers->timing_mutex);
		philosophers->info->finished_eating++;
		pthread_mutex_unlock(&philosophers->timing_mutex);
		return(-1);
	}
	return(1);
}

int start_eat_odd(t_philo *philosophers)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	left_fork = &philosophers->posate_mutex;
	right_fork = &(philosophers->primo_philo[(philosophers->id % philosophers->info->n_of_philos)].posate_mutex);
	pthread_mutex_lock(right_fork);
	pthread_mutex_lock(left_fork);
	if (philo_print(philosophers, "has taken right fork") < 0)
		return ( pthread_mutex_unlock(right_fork), -1);
	if (philo_print(philosophers, "has taken left fork") < 0)
		return (pthread_mutex_unlock(right_fork), pthread_mutex_unlock(left_fork), -1);
	get_new_time(philosophers);
	
	if (philo_print(philosophers, "is eating") < 0)
		return ( pthread_mutex_unlock(right_fork), pthread_mutex_unlock(left_fork), -1);
	sleep_and_check(philosophers->info->time_to_eat, philosophers);
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
	if(++philosophers->n_meals == philosophers->info->meals)
	{
		pthread_mutex_lock(&philosophers->timing_mutex);
		philosophers->info->finished_eating++;
		pthread_mutex_unlock(&philosophers->timing_mutex);
		return(-1);
	}
	return(1);
}


int forced_check(t_philo *philosophers)
{
	if (philosophers->info->meals == 0)
		return(-1);
	if(philosophers->info->is_dead == 1)
		return(-1);
	if( philosophers->info->n_of_philos == 1)
	{
		printf("0 1 is thinking\n");
		printf("0 1 is has taken right fork\n");
		return(-1);
	}
	return(1);
}



void *philo_routine(void *arg)
{
	t_philo *philosophers;

	philosophers = (t_philo *) arg;
	init_time(philosophers);
	if(forced_check(philosophers) == -1)
		return(NULL);

	while(!philosophers->info->is_dead)
	{
		if (philosophers->info->is_dead == 0 && (philosophers->id % 2 == 0))
		{
			get_new_start(philosophers);
			if(philosophers->info->is_dead == 0)
				printf("%lld %d is thinking\n", philosophers->philo_s_time, philosophers->id);
			else
				return(NULL);
			
			while (!philosophers->info->is_dead) 
			{
        		if (dispari_uguali(philosophers) && tutti_i_dispari_uguali_a_me(philosophers))
            		break;
    		}
			if(start_eat(philosophers) < 0)
				return (NULL);
		
			if(philosophers->info->is_dead == 0)
			{
				if(philosophers->info->is_dead == 0)
				{
					printf("%lld %d is sleeping\n",  philosophers->philo_s_time, philosophers->id);
					if(sleep_and_check(philosophers->info->time_to_sleep ,philosophers) == -1)
						return(NULL);
				}
			}
			else
				return(NULL);
		}
		else if (philosophers->info->is_dead == 0 && philosophers->id % 2 == 1)
		{
			get_new_start(philosophers);
			if(philosophers->n_meals != 0)
			{
				if(philosophers->info->is_dead == 0)
					printf("%lld %d is thinking\n", philosophers->philo_s_time, philosophers->id);
				else
					return(NULL);
			}
			while (!philosophers->info->is_dead) 
			{
        		if (pari_uguali(philosophers) && tutti_i_pari_maggiore(philosophers))
            		break;
    		}
			get_new_start(philosophers);
			if(philosophers->info->is_dead == 0 && philosophers->info->n_of_philos % 2 == 1)
			{
				if(philosophers->info->is_dead == 0 && philosophers->id == philosophers->info->n_of_philos)
				{
					if(start_eat_odd(philosophers) < 0)
						return(NULL);
				}
				else
				{
					while(philosophers->primo_philo[philosophers->info->n_of_philos-1].n_meals == philosophers->n_meals);
					if (start_eat_odd(philosophers) < 0)
						return (NULL);
				}
			}
			else
			{
				if(philosophers->info->is_dead == 0)
				{	if (start_eat_odd(philosophers) < 0)
						return (NULL);
				}
			}
			if(philosophers->info->is_dead == 0)
			{
				printf("%lld %d is sleeping\n",  philosophers->philo_s_time, philosophers->id);
				if(sleep_and_check(philosophers->info->time_to_sleep ,philosophers) == -1)
				{
					return(NULL);
				}
							
			}
			else
				return(NULL);
		}
		get_new_start(philosophers);
		if (philosophers->info->meals == 0)
		{
			return(NULL);
		}
			
	}
	return(NULL);
}
