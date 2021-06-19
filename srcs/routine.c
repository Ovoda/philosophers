/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/19 11:58:00 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *routine(void *arg)
{
	t_params params;
	t_philo philo;
	int i = 0;
	int begin;
	int ms_current_time;
	struct timeval current_time;

	philo = ((t_params *)(arg))->global->philo[((t_params *)(arg))->i];
	params = *(t_params *)arg;
	begin = 0;
	gettimeofday(&current_time, NULL);
	philo.last_meal = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	while (1)
	{
		if (begin == 0 && philo.id % 2 != 0)
		{
			ft_usleep(10);
			begin = 1;
		}
		gettimeofday(&current_time, NULL);
		ms_current_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		printf("%d last meal was %d\n", philo.id, ms_current_time - philo.last_meal);
		if (ms_current_time - philo.last_meal > params.global->tto_die)
		{
			printf("\n\n %d DIED last meal was %d\n \n", philo.id, philo.last_meal - params.global->ms_start);
		}
		gettimeofday(&current_time, NULL);
		philo.last_meal = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		philo_eat(&params);
		//printf("\n\nLAST MEAL %d = %d\n\n", philo.id,  philo.last_meal - params.global->ms_start);
		philo_sleep(&params);
		philo_think(&params);
	}
	return (NULL);
}