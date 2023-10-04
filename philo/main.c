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

int init_struct(t_philo **philosophers, t_info *info)
{
	*philosophers = NULL;
	*philosophers = malloc(sizeof(t_philo) * info->n_of_philos); //filosofi
	if(!*philosophers)
		return(-1);
	(*philosophers)->info = info;
	return 0;
}

void join_all(t_philo *philosophers)
{
	int i=0;
	while(i < philosophers->info->n_of_philos)
	{
		pthread_join(philosophers[i].philo, NULL);
		i++;
	}
}

int init_monitor_all_eat(t_philo *philosophers)
{
	while(!philosophers->info->is_dead)
	{
		if(pari_uguali(philosophers) && philosophers->n_meals == philosophers->info->meals)
			return(1);
	}
	return(0);
}


int main(int argc, char** argv)
{
	t_philo *philosophers;
	t_info info;
	pthread_t monitor_t;

	if(init_info(&info, argv, argc) == -1)
		return(printf("Args errati...\n"));
	init_struct(&philosophers, &info);
	if(init_mutexes(&info.start_mutex, &info.end_mutex, &info.finish_eat_mutex) == -1)
		return(free(philosophers), 0);
	init_threads(philosophers);
	pthread_create(&monitor_t, NULL, monitor, philosophers);
	pthread_join(monitor_t, NULL);
	join_all(philosophers);
}
