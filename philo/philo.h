/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 23:39:44 by shhuang           #+#    #+#             */
/*   Updated: 2023/09/20 23:39:44 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define USECONDS_TO_S 1000000LL
# define USECONDS_TO_MS 1000LL

typedef struct s_info
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_philos;
	int				meals;
	int				is_dead;
	int				finished_eating;
	pthread_mutex_t	start;
	pthread_mutex_t	end;
	pthread_mutex_t	finish_eat;
} t_info;

typedef struct s_philo
{
	int				id;
	struct timeval	start_time;
	struct timeval	death_time;
	pthread_mutex_t	timing_mutex;
	pthread_mutex_t	fork;
	pthread_t		philo;
	struct s_philo	*filosofi;
	t_info	*info;
} t_philo;


#endif