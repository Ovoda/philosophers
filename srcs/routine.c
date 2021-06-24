/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/22 13:19:05 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t sub_t(time_t ms)
{
	return (get_time() - ms);
}

void *routine(void *arg)
{
	t_philo *philo;
	int i;

	i = -1;
	philo = (t_philo *)(arg);
	while (++i < philo->nb_eat || (philo->nb_eat == -1))
	{
		pthread_mutex_lock((philo->ag_mutex));
		if (*philo->all_good == -1)
			return (NULL);
		pthread_mutex_unlock((philo->ag_mutex));
		pthread_mutex_lock(&philo->mutex[philo->own_fork]);
		printf("%06ld %d has taken fork\n", sub_t(philo->ms), philo->id + 1);
		pthread_mutex_lock(&philo->mutex[philo->next_fork]);
		printf("%06ld %d has taken fork\n", sub_t(philo->ms), philo->id + 1);
		printf("%06ld %d is eating\n", sub_t(philo->ms), philo->id + 1);
		pthread_mutex_lock(&philo->lm_mutex);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->lm_mutex);
		ft_usleep(philo->tto_eat, philo->all_good);
		pthread_mutex_lock((philo->ag_mutex));
		*(philo->all_good) += 1;
		pthread_mutex_unlock((philo->ag_mutex));
		pthread_mutex_unlock(&philo->mutex[philo->next_fork]);
		pthread_mutex_unlock(&philo->mutex[philo->own_fork]);
		printf("%06ld %d is sleeping\n", sub_t(philo->ms), philo->id + 1);
		ft_usleep(philo->tto_sleep, philo->all_good);
		printf("%06ld %d is thinking\n", sub_t(philo->ms), philo->id + 1);
	}
	return (NULL);
}

void start_half_thread(t_philo *philo, int i, int *all_good, time_t now)
{

	while (i < philo->nb_philo)
	{
		philo[i].last_meal = get_time();
		philo[i].ms = now;
		philo[i].all_good = all_good;
		pthread_create(&(philo[i].thread), NULL, routine, &philo[i]);
		//pthread_detach(philo[i].thread);
		i += 2;
	}
}

void *monitor(void *arg)
{
	t_philo *philo;
	int i;
	int ok;

	ok = 1;
	philo = (t_philo *)arg;
	while (ok)
	{
		i = -1;
		while (++i < philo->nb_philo && ok)
		{
			pthread_mutex_lock((philo->ag_mutex));
			if (*philo->all_good == philo->nb_philo * philo->nb_eat)
			{
				pthread_mutex_unlock((philo->ag_mutex));
				return (NULL);
			}
			pthread_mutex_lock(&philo[i].lm_mutex);
			if (get_time() - philo[i].last_meal > philo->tto_die)
			{
				printf("%06ld %d died\n", sub_t(philo->ms), philo[i].id + 1);
				ok = 0;
				*philo->all_good = -1;
				return (NULL);
			}
			pthread_mutex_unlock(&philo[i].lm_mutex);
			pthread_mutex_unlock((philo->ag_mutex));
		}
		usleep(100);
	}
	return (NULL);
}

void run_philo(t_philo *philo)
{
	time_t now;
	pthread_t thread;
	int all_good;

	now = get_time();
	all_good = 0;
	start_half_thread(philo, 0, &all_good, now);
	ft_usleep(100, philo->all_good);
	start_half_thread(philo, 1, &all_good, now);
	pthread_create(&thread, NULL, monitor, philo);
	pthread_join(thread, NULL);
	int i;

	i = -1;
	while (++i < philo->nb_philo)
		pthread_detach(philo[i].thread);
}
