/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:05:11 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/20 14:13:41 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo *init_philo(t_global *global, pthread_mutex_t *mutex)
{
	t_philo *philo;
	int i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * (global->nb_philo));
	if (!philo)
		return (NULL);
	while (++i < global->nb_philo)
	{
		philo[i].id = i;
		philo[i].nb_eat = global->nb_eat;
		philo[i].own_fork = i;
		philo[i].all_good = 0;
		philo[i].next_fork = i - 1;
		if (i - 1 < 0)
			philo[i].next_fork = global->nb_philo - 1;
		philo[i].nb_philo = global->nb_philo;
		philo[i].ms_start = global->ms_start;
		philo[i].tto_eat = global->tto_eat;
		philo[i].tto_die = global->tto_die;
		philo[i].tto_sleep = global->tto_sleep;
		philo[i].mutex = mutex;
	}
	return (philo);
}

void start_half_thread(t_philo *philo, int i, int *alive, time_t now)
{
	while (i < philo->nb_philo)
	{
		philo[i].last_meal = get_time();
		philo[i].ms_start = now;
		philo[i].alive = alive;
		pthread_create(&(philo[i].thread), NULL, routine, &philo[i]);
		pthread_detach(philo[i].thread);
		i += 2;
	}
}

void run_philo(t_philo *philo, pthread_mutex_t *mutex)
{
	int alive;
	int i;
	int all_good;
	time_t now;

	alive = 1;
	all_good = 0;
	now = get_time();
	start_half_thread(philo, 0, &alive, now);
	usleep(100);
	start_half_thread(philo, 1, &alive, now);
	while (alive)
	{
		i = -1;
		while (++i < philo->nb_philo)
			if (philo[i].all_good == 1)
				all_good += 1;
		if (all_good >= philo->nb_philo - 1 && philo->nb_eat != -1)
			return;
		else
			all_good = 0;
		i = -1;
		while (++i < philo->nb_philo)
		{
			if (ft_get_time(philo->ms_start) - philo[i].last_meal > philo->tto_die)
			{
				printf("%06ld %d died\n", get_time() - philo->ms_start, philo[i].id);
				return;
			}
		}
		usleep(1000);
	}
}

int philo(t_global *global)
{
	pthread_mutex_t *mutex;
	t_philo *philo;
	int	i;

	i = -1;
	mutex = init_mutex(global);
	philo = init_philo(global, mutex);
	run_philo(philo, mutex);
	destroy_mutex(philo);
	free(philo);
	free(mutex);
	free(global);
	return (0);
}