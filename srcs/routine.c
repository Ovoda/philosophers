/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/20 13:02:23 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *routine(void *arg)
{
	t_philo *philo;
	int begin;

	philo = (t_philo *)(arg);
	philo->last_meal = 0;
	begin = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex[philo->own_fork]);
		pthread_mutex_lock(&philo->mutex[philo->next_fork]);
		printf("%06ld %d has taken own fork\n", get_time() - philo->ms_start, philo->id);
		printf("%06ld %d has taken next fork\n", get_time() - philo->ms_start, philo->id);
		printf("%06ld %d is eating\n", get_time() - philo->ms_start, philo->id);
		philo->last_meal = ft_get_time(philo->ms_start);
		ft_usleep(philo->tto_eat);
		pthread_mutex_unlock(&philo->mutex[philo->next_fork]);
		pthread_mutex_unlock(&philo->mutex[philo->own_fork]);
		printf("%06ld %d is sleeping\n", get_time() - philo->ms_start, philo->id);
		ft_usleep(philo->tto_sleep);
		printf("%06ld %d is thinking\n", get_time() - philo->ms_start, philo->id);
	}
	return (NULL);
}