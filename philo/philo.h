/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:08:45 by jlyu              #+#    #+#             */
/*   Updated: 2023/08/23 16:02:04 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_param
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_num;
	struct timeval	timestamp;
}	t_param;

typedef struct s_philosopher
{
	int				id;
	pthread_mutex_t	stop;
	int				left_fork;
	int				right_fork;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_num;
	struct timeval	timestamp;
	struct timeval	last_eat;
	pthread_t		thread;
	pthread_mutex_t	*forks;
}	t_philosopher;

void	philo(int args, char *argv[]);

void	philo_atoi(t_param *param, int args, char *argv[]);
void	philo_eating(t_philosopher *philosopher);
void	philo_sleeping(t_philosopher *philosopher);
void	philo_thinking(t_philosopher *philosopher);

#endif