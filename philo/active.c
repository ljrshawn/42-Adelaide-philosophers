/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:54:44 by jlyu              #+#    #+#             */
/*   Updated: 2023/08/23 16:01:39 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*timer_function(void *arg)
{
	t_philosopher	*philosopher;
	struct timeval	timestamp;

	philosopher = (t_philosopher *)arg;
	usleep(1000 * philosopher->time_die);
	gettimeofday(&timestamp, NULL);
	if ((((timestamp.tv_sec - philosopher->last_eat.tv_sec)
				* 1000000 + timestamp.tv_usec - philosopher->last_eat.tv_usec)
			/ 1000) >= philosopher->time_die)
	{
		printf("%ld %d died\n",
			((timestamp.tv_sec - philosopher->timestamp.tv_sec)
				* 1000000 + timestamp.tv_usec - philosopher->timestamp.tv_usec)
			/ 1000, philosopher->id);
		pthread_mutex_lock(&(philosopher->stop));
		pthread_mutex_unlock(&(philosopher->forks[philosopher->left_fork]));
		pthread_mutex_unlock(&(philosopher->forks[philosopher->right_fork]));
	}
	return (NULL);
}

void	philo_eating(t_philosopher *philosopher)
{
	pthread_t		thread;
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	printf("%ld %d has taken a fork\n",
		((timestamp.tv_sec - philosopher->timestamp.tv_sec)
			* 1000000 + timestamp.tv_usec - philosopher->timestamp.tv_usec)
		/ 1000, philosopher->id);
	printf("%ld %d has taken a fork\n",
		((timestamp.tv_sec - philosopher->timestamp.tv_sec)
			* 1000000 + timestamp.tv_usec - philosopher->timestamp.tv_usec)
		/ 1000, philosopher->id);
	philosopher->last_eat = timestamp;
	printf("%ld %d is eating\n",
		((timestamp.tv_sec - philosopher->timestamp.tv_sec)
			* 1000000 + timestamp.tv_usec - philosopher->timestamp.tv_usec)
		/ 1000, philosopher->id);
	if (pthread_create(&(thread), NULL,
			timer_function, philosopher) != 0)
		return ;
	pthread_detach(thread);
	usleep(1000 * philosopher->time_eat - 900);
}

void	philo_sleeping(t_philosopher *philosopher)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	printf("%ld %d is sleeping\n",
		((timestamp.tv_sec - philosopher->timestamp.tv_sec)
			* 1000000 + timestamp.tv_usec - philosopher->timestamp.tv_usec)
		/ 1000, philosopher->id);
	usleep(1000 * philosopher->time_sleep);
}

void	philo_thinking(t_philosopher *philosopher)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	printf("%ld %d is thinking\n",
		((timestamp.tv_sec - philosopher->timestamp.tv_sec)
			* 1000000 + timestamp.tv_usec - philosopher->timestamp.tv_usec)
		/ 1000, philosopher->id);
}
