/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:02:16 by jlyu              #+#    #+#             */
/*   Updated: 2023/08/23 16:01:56 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_function(void *arg)
{
	t_philosopher	*philosopher;
	int				i;

	philosopher = (t_philosopher *)arg;
	i = philosopher->times_num;
	if (i == -1)
		i = 1;
	while (i > 0)
	{
		pthread_mutex_lock(&(philosopher->forks[philosopher->left_fork]));
		pthread_mutex_lock(&(philosopher->forks[philosopher->right_fork]));
		pthread_mutex_lock(&(philosopher->stop));
		philo_eating(philosopher);
		pthread_mutex_unlock(&(philosopher->forks[philosopher->left_fork]));
		pthread_mutex_unlock(&(philosopher->forks[philosopher->right_fork]));
		pthread_mutex_unlock(&(philosopher->stop));
		philo_sleeping(philosopher);
		philo_thinking(philosopher);
		if (philosopher->times_num == -1)
			i = 2;
		i--;
	}
	gettimeofday(&(philosopher->last_eat), NULL);
	return (NULL);
}

void	initial_fork(pthread_mutex_t *forks, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_init(&(forks[i]), NULL);
		i++;
	}
}

void	set_feature(t_philosopher *philosophers, t_param *param,
	pthread_mutex_t *forks, int philo_n)
{
	if (philo_n == 0)
		philosophers[philo_n].left_fork = param->philo_num - 1;
	else
		philosophers[philo_n].left_fork = philo_n - 1;
	philosophers[philo_n].right_fork = philo_n;
	philosophers[philo_n].id = philo_n + 1;
	philosophers[philo_n].time_die = param->time_die;
	philosophers[philo_n].time_eat = param->time_eat;
	philosophers[philo_n].time_sleep = param->time_sleep;
	philosophers[philo_n].times_num = param->times_num;
	philosophers[philo_n].timestamp = param->timestamp;
	philosophers[philo_n].forks = forks;
	pthread_mutex_init(&(philosophers[philo_n].stop), NULL);
}

void	philo_util(t_param *param, t_philosopher *philosophers,
	pthread_mutex_t *forks)
{
	int				philo_n;

	philo_n = 0;
	gettimeofday(&(param->timestamp), NULL);
	while (philo_n < param->philo_num)
	{
		set_feature(philosophers, param, forks, philo_n);
		if (pthread_create(&(philosophers[philo_n].thread), NULL,
				thread_function, &(philosophers[philo_n])) != 0)
			return ;
		pthread_detach(philosophers[philo_n].thread);
		philo_n++;
	}
	usleep(100000 * param->time_die);
	free(param);
	free(forks);
	free(philosophers);
}

void	philo(int args, char *argv[])
{
	t_philosopher	*philosophers;
	t_param			*param;
	pthread_mutex_t	*forks;

	param = malloc(1 * sizeof(t_param));
	if (param == NULL)
		return ;
	philo_atoi(param, args, argv);
	if (param->philo_num == 1)
	{
		usleep(1000 * param->time_die);
		printf("%d %d died\n", param->time_die, 1);
		free(param);
		return ;
	}
	forks = malloc(param->philo_num * sizeof(pthread_mutex_t));
	if (forks == NULL)
		return ;
	initial_fork(forks, param->philo_num);
	philosophers = malloc(param->philo_num * sizeof(t_philosopher));
	if (philosophers == NULL)
		return ;
	philo_util(param, philosophers, forks);
}
