#include "philo.h"

long long get_time_in_milliseconds(void)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    
	//prendo i secondi e li moltiplico per mille per raggiungere un valore di millisecondi, divido i microsecondi per 1000

    long long milliseconds = (long long)current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    
    return milliseconds;
}

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
