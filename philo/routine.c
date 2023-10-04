#include "philo.h"

void add_death_time(t_philo *philosophers)
{
	philosophers->philo_d_time = philosophers->philo_s_time + (long long int)philosophers->info->time_to_die;
}

void get_new_start(t_philo *philosophers)
{
	philosophers->philo_s_time = get_time_in_milliseconds() - philosophers->philo_first_s_time ;
}

void get_new_time(t_philo *philosophers)
{
	get_new_start(philosophers);
	add_death_time(philosophers);
}

void init_time(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->timing_mutex);
	philosophers->philo_first_s_time = get_time_in_milliseconds();
	get_new_time(philosophers);
	pthread_mutex_unlock(&philosophers->timing_mutex);
}


void wait_to_eat(t_philo *philosophers)
{
	usleep(philosophers->info->time_to_eat * 1000);
	get_new_start(philosophers);
	if(philosophers->philo_s_time >= philosophers->philo_d_time)
		philosophers->info->is_dead = philosophers->id;
}


int	philo_print(t_philo *philosophers, char *message)
{
	pthread_mutex_lock(&philosophers->info->end_mutex);
	if (philosophers->info->is_dead == 0 && philosophers->info->finished_eating < philosophers->info->n_of_philos)
	{
		get_new_start(philosophers);
		printf("%lld %d %s\n", philosophers->philo_s_time, philosophers->id, message);
		pthread_mutex_unlock(&philosophers->info->end_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philosophers->info->end_mutex);
	return (-1);
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
		usleep(900);
		get_new_start(philosophers);
	}
	return(0);
}

int start_eat(t_philo *philosophers)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	left_fork = &philosophers->posate_mutex;
	right_fork = &(philosophers->primo_philo[(philosophers->id % philosophers->info->n_of_philos)].posate_mutex);

	pthread_mutex_lock(left_fork);
	if (philo_print(philosophers, "has taken left fork") < 0 || philosophers->info->n_of_philos == 1)
		return (pthread_mutex_unlock(left_fork), -1);
	
	pthread_mutex_lock(right_fork);
	if (philo_print(philosophers, "has taken right fork") < 0)
		return (pthread_mutex_unlock(left_fork) ,pthread_mutex_unlock(right_fork), -1);
	get_new_time(philosophers);
	if (philo_print(philosophers, "is eating") < 0)
		return (pthread_mutex_unlock(left_fork) ,pthread_mutex_unlock(right_fork), -1);
	
	sleep_and_check(philosophers->info->time_to_eat, philosophers);
	philosophers->n_meals += 1;
	if(philosophers->n_meals == philosophers->info->meals)
	{
		pthread_mutex_lock(&philosophers->timing_mutex);
		philosophers->info->finished_eating++;
		pthread_mutex_unlock(&philosophers->timing_mutex);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		return(-1);
	}
	
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	return(1);
}

int start_eat_odd(t_philo *philosophers)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	left_fork = &philosophers->posate_mutex;
	right_fork = &(philosophers->primo_philo[(philosophers->id % philosophers->info->n_of_philos)].posate_mutex);
	
	pthread_mutex_lock(right_fork);
	if (philo_print(philosophers, "has taken right fork") < 0)
		return ( pthread_mutex_unlock(right_fork), -1);

	pthread_mutex_lock(left_fork);
	if (philo_print(philosophers, "has taken left fork") < 0 || philosophers->info->n_of_philos == 1)
		return (pthread_mutex_unlock(right_fork), pthread_mutex_unlock(left_fork), -1);
	get_new_time(philosophers);
	if (philo_print(philosophers, "is eating") < 0)
		return ( pthread_mutex_unlock(right_fork), pthread_mutex_unlock(left_fork), -1);
	
	sleep_and_check(philosophers->info->time_to_eat, philosophers);
	philosophers->n_meals += 1;
	
	if(philosophers->n_meals == philosophers->info->meals)
	{
		pthread_mutex_lock(&philosophers->timing_mutex);
		philosophers->info->finished_eating++;
		pthread_mutex_unlock(&philosophers->timing_mutex);
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
		return(-1);
	}
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
	return(1);
}

bool tutti_uguali(t_philo *philosophers) 
{
    int i = 0;
    while (!philosophers->info->is_dead && i < philosophers->info->n_of_philos) 
	{
		if (philosophers->primo_philo[i].n_meals != philosophers->primo_philo[(i-1 + philosophers->info->n_of_philos) % philosophers->info->n_of_philos].n_meals)
		{
            return false;
        }
        i += 2;
    }
    return true;
}

bool pari_uguali(t_philo *philosophers) {
    int i = 1;
    while (!philosophers->info->is_dead && i < philosophers->info->n_of_philos) 
	{
		if (philosophers->primo_philo[i].n_meals != philosophers->primo_philo[(i-2 + philosophers->info->n_of_philos) % philosophers->info->n_of_philos].n_meals)
		{
            return false;
        }
        i++;
    }
    return true;
}

bool tutti_i_pari_maggiore(t_philo *philosophers) 
{
    int i = 1;
    while (!philosophers->info->is_dead && i < philosophers->info->n_of_philos) 
	{
        if (philosophers->primo_philo[i].n_meals == philosophers->n_meals)
		{
            return false;
        }
        i += 2;
    }
    return true;
}

void *philo_routine(void *arg)
{
	t_philo *philosophers;

	philosophers = (t_philo *) arg;
	init_time(philosophers);

	if( philosophers->info->n_of_philos == 1 && philosophers->n_meals != 0)
	{
		printf("0 1 is thinking\n");
		printf("0 1 is has taken right fork\n");
		printf("%d 1 is has died\n", philosophers->info->time_to_die);
		return(NULL);
	}

	if (philosophers->id % 2 == 1)
		wait_to_eat(philosophers);
	if (philosophers->info->meals == 0)
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
			while(philosophers->info->is_dead == 0 && philosophers->n_meals > philosophers->primo_philo[philosophers->id % philosophers->info->n_of_philos].n_meals)
				usleep(1);
			if(start_eat(philosophers) < 0)
				return (NULL);
		
			if(philosophers->info->is_dead == 0)
			{
				printf("%lld %d is sleeping\n",  philosophers->philo_s_time, philosophers->id);
				if(sleep_and_check(philosophers->info->time_to_sleep ,philosophers) == -1)
					return(NULL);
			}
			else
				return(NULL);
		}
		else if (philosophers->info->is_dead == 0 && philosophers->id % 2 == 1)
		{
			get_new_start(philosophers);
			if(philosophers->info->is_dead == 0)
				printf("%lld %d is thinking\n", philosophers->philo_s_time, philosophers->id);
			else
				return(NULL);
			 while (!philosophers->info->is_dead) 
			 {
        		if (pari_uguali(philosophers) && tutti_i_pari_maggiore(philosophers))
            		break;
    		}
			if(start_eat_odd(philosophers) < 0)
				return (NULL);
			if(philosophers->info->is_dead == 0)
			{
				printf("%lld %d is sleeping\n",  philosophers->philo_s_time, philosophers->id);
				if(sleep_and_check(philosophers->info->time_to_sleep ,philosophers) == -1)
					return(NULL);		
			}
			else
				return(NULL);
		}
		get_new_start(philosophers);
		if (philosophers->info->meals == 0)
			return(NULL);
	}
	return(NULL);
}
