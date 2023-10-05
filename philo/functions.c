/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 04:28:45 by shhuang           #+#    #+#             */
/*   Updated: 2023/09/21 04:28:45 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned int		i;
	int					sign;
	long				result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit((int)str[i]))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return ((int)sign * result);
}

int err(t_philo *philosophers)
{
	philosophers->info->err = 1;
	return(1);
}

bool pari_uguali(t_philo *philosophers) 
{
    int i = 1;
    while (!philosophers->info->is_dead && i < philosophers->info->n_of_philos) 
	{
		if (philosophers->info->n_of_philos % 2 == 1 && i == (philosophers->info->n_of_philos - 2))
            break;
		if (philosophers->primo_philo[i].n_meals != philosophers->primo_philo[(i+2 + philosophers->info->n_of_philos) % philosophers->info->n_of_philos].n_meals)
		{
            return false;
        }
        i+=2;
    }
    return true;
}

bool tutti_i_pari_maggiore(t_philo *philosophers) 
{
    int i = 1;
    while (!philosophers->info->is_dead && i < philosophers->info->n_of_philos) 
	{
		if (philosophers->info->n_of_philos % 2 == 1 && i == (philosophers->info->n_of_philos - 2))
            break;
		if(philosophers->primo_philo[0].n_meals > philosophers->n_meals)
			return(true);
        if (philosophers->primo_philo[i].n_meals == philosophers->n_meals)
		{
            return false;
        }
        i += 2;
    }
    return true;
}

bool dispari_uguali(t_philo *philosophers) 
{
    int i = 0;
    while (!philosophers->info->is_dead && i < philosophers->info->n_of_philos-1) 
    {
        if (philosophers->primo_philo[i].n_meals != philosophers->primo_philo[(i-2 + philosophers->info->n_of_philos) % philosophers->info->n_of_philos].n_meals)
        {
            return false;
        }
        i += 2;
    }
    return true;
}

bool tutti_i_dispari_uguali_a_me(t_philo *philosophers) 
{
    int i = 0;
    while (!philosophers->info->is_dead && i < philosophers->info->n_of_philos-1) 
	{
        if (philosophers->primo_philo[i].n_meals < philosophers->n_meals)
		{
            return false;
        }
        i += 2;
    }
    return true;
}