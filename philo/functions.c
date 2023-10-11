/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 00:48:28 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/11 00:48:28 by shhuang          ###   ########.fr       */
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
	unsigned int	i;
	int				sign;
	long			result;

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

int	err(t_philo *philosophers)
{
	philosophers->info->err = 1;
	return (1);
}

void	check_and_print(t_philo *philosophers, char *str)
{
	if (!philosophers->info->is_dead)
		printf("%lld %d %s\n", philosophers->philo_s_time, philosophers->id,
			str);
}
