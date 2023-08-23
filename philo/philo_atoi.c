/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:48:39 by jlyu              #+#    #+#             */
/*   Updated: 2023/08/23 13:29:50 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_philo_atoi(const char *str)
{
	unsigned int	res;
	int				flag;

	res = 0;
	flag = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			flag = -1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			res = res * 10 + (*str - '0');
		else
			break ;
		str++;
	}
	return (res * flag);
}

void	philo_atoi(t_param *param, int args, char *argv[])
{
	param->philo_num = _philo_atoi(argv[0]);
	param->time_die = _philo_atoi(argv[1]);
	param->time_eat = _philo_atoi(argv[2]);
	param->time_sleep = _philo_atoi(argv[3]);
	param->times_num = -1;
	if (args == 5)
		param->times_num = _philo_atoi(argv[4]);
}
