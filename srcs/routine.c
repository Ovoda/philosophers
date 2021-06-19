/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/19 14:10:01 by calide-n         ###   ########.fr       */
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
		if (begin == 0 && philo->id % 2 != 0)
		{
			ft_usleep(100);
			begin = 1;
		}
		philo_eat(philo);
		print_message(*philo, ACTION_SLEEP);
    	ft_usleep(philo->tto_sleep);
		print_message(*philo, ACTION_THINK);
	}
	return (NULL);
}