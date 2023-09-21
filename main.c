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

void init_info(t_info *info, char **argv, int argc)
{
	info->n_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		info->meals = ft_atoi(argv[5]);
	else
		info->meals = 0;
}

int main(int argc, char** argv)
{
	t_philo *philosophers;
	t_info *info;
	if(argc == 5 || argc == 6)
	{
	info = malloc(sizeof(t_info));
	init_info(info, argv, argc);
	philosophers = malloc(sizeof(t_philo) * info->n_of_philos);
	philosophers->info = &info;
	}
}