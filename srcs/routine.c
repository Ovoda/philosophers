/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 22:09:06 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *routine(void *arg)
{
	t_params    	*params;
	t_philo			philo;
	int				i = 0;
	int				begin;
	int				ms_current_time;
	struct timeval	current_time;

	philo = ((t_params *)(arg))->global->philo[((t_params *)(arg))->i];
	params = (t_params *)arg;
	begin = 0;
	while (++i < 10)
	{
		gettimeofday(&current_time, NULL);
		ms_current_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		if (begin == 0 && philo.id % 2 != 0)
		{
			ft_usleep(10);
			begin = 1;
		}
		philo_eat(philo);
		gettimeofday(&current_time, NULL);
		philo.last_meal = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}