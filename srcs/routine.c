/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/19 17:09:55 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *routine(void *arg)
{
	t_philo philo;
	int begin;

	struct timeval start;
	int ms_start;

	philo = *(t_philo *)(arg);
	philo.last_meal = 0;
	begin = 0;
	while (1)
	{
		if (begin == 0 && philo.id % 2 != 0)
		{
			ft_usleep(100);
			begin = 1;
		}
		pthread_mutex_lock(&philo.mutex[philo.own_fork]);
		print_message(philo, ACTION_FORK);
		pthread_mutex_lock(&philo.mutex[philo.next_fork]);
		print_message(philo, ACTION_FORK);
		print_message(philo, ACTION_EAT);
		philo.last_meal = ft_get_time(philo.ms_start);
		ft_usleep(philo.tto_eat);
		pthread_mutex_unlock(&philo.mutex[philo.own_fork]);
		pthread_mutex_unlock(&philo.mutex[philo.next_fork]);
		print_message(philo, ACTION_SLEEP);
		ft_usleep(200);
		print_message(philo, ACTION_THINK);
	}
	return (NULL);
}