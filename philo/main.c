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

void join_all(t_philo *philosophers)
{
	int i=0;
	while(i < philosophers->info->n_of_philos)
	{
		pthread_join(philosophers[i].philo, NULL);
		i++;
	}
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
