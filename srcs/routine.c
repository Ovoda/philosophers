/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/20 14:23:07 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *routine(void *arg)
{
	t_philo *philo;
	int begin;
	int i;

	i = -1;
	philo = (t_philo *)(arg);
	begin = 0;
	while (++i < philo->nb_eat || (philo->nb_eat == -1))
	{
		pthread_mutex_lock(&philo->mutex[philo->own_fork]);
		pthread_mutex_lock(&philo->mutex[philo->next_fork]);
		printf("%06ld %d has taken own fork\n", get_time() - philo->ms_start, philo->id);
		printf("%06ld %d has taken next fork\n", get_time() - philo->ms_start, philo->id);
		printf("%06ld %d is eating\n", get_time() - philo->ms_start, philo->id);
		philo->last_meal = get_time();
		ft_usleep(philo->tto_eat);
		printf("%06ld %d is sleeping\n", get_time() - philo->ms_start, philo->id);
		pthread_mutex_unlock(&philo->mutex[philo->next_fork]);
		pthread_mutex_unlock(&philo->mutex[philo->own_fork]);
		ft_usleep(philo->tto_sleep);
		printf("%06ld %d is thinking\n", get_time() - philo->ms_start, philo->id);
	}
	philo->all_good = 1;
	return (NULL);
}