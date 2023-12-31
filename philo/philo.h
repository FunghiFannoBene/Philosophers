/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <shhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:04:16 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/11 23:04:16 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

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
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	finish_eat_mutex;
}	t_info;

typedef struct s_philo
{
	int				id;
	long long int	philo_s_time;
	long long int	philo_d_time;
	long long int	philo_first_s_time;
	int				n_meals;
	pthread_mutex_t	death_timing;
	pthread_mutex_t	timing_mutex;
	pthread_mutex_t	posate_mutex;
	pthread_t		philo;
	struct s_philo	*primo_philo;
	struct s_info	*info;
}	t_philo;

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	get_time_in_milliseconds(void);
int			start_eat(t_philo *philosophers, pthread_mutex_t *left,
				pthread_mutex_t *right);
int			init_info(t_info *info, char **argv, int argc);
int			init_mutexes(pthread_mutex_t *m1, pthread_mutex_t *m2);
int			init_threads(t_philo *philosophers);
long long	get_time_in_milliseconds(void);
void		*philo_routine(void *arg);
int			err(t_philo *philosophers);
void		*monitor(void *arg);
int			init_struct(t_philo **philosophers, t_info *info);
void		get_new_start(t_philo *philosophers);
int			init_struct(t_philo **philosophers, t_info *info);
void		get_new_time(t_philo *philosophers);
void		unlock_right(pthread_mutex_t *fork);
void		unlock_left(pthread_mutex_t *fork);
int			lock_right(pthread_mutex_t *fork, t_philo *philosophers);
void		lock_left(pthread_mutex_t *fork, t_philo *philosophers);
int			forced_check(t_philo *philosophers);
void		check_and_print(t_philo *philosophers, char *str);
void		check_and_print_death(t_philo *philosophers, char *str);
void		init_time(t_philo *philosophers);

#endif