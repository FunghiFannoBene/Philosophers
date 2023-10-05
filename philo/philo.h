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
# include <stdbool.h>

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
	int				err;
	int				finished_eating;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	finish_eat_mutex;
} t_info;

typedef struct s_philo
{
	int				id;
	long long int	philo_s_time;
	long long int	philo_d_time;
	long long int	philo_first_s_time;
	int				n_meals;
	pthread_mutex_t	timing_mutex;
	pthread_mutex_t	posate_mutex;
	pthread_t		philo;
	struct s_philo	*primo_philo;
	struct s_info	*info;
} t_philo;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
long long get_time_in_milliseconds(void);
int init_info(t_info *info, char **argv, int argc);
int	init_mutexes(pthread_mutex_t *m1, pthread_mutex_t *m2, pthread_mutex_t *m3);
int init_threads(t_philo *philosophers);
long long get_time_in_milliseconds(void);
void *philo_routine(void *arg);
int err(t_philo *philosophers);
void *monitor(void *arg);
int init_struct(t_philo **philosophers, t_info *info);
bool pari_uguali(t_philo *philosophers);
void get_new_start(t_philo *philosophers);
int init_struct(t_philo **philosophers, t_info *info);
void add_death_time(t_philo *philosophers);
void get_new_time(t_philo *philosophers);
bool tutti_i_pari_maggiore(t_philo *philosophers);
int sleep_and_check(long long int eat, t_philo *philosophers);
void wait_to_eat(t_philo *philosophers);
bool tutti_i_dispari_uguali_a_me(t_philo *philosophers);
bool dispari_uguali(t_philo *philosophers);

#endif