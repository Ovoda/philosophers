/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/24 15:58:38 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex[philo->own_fork]);
	print_message("has taken fork", philo);
	pthread_mutex_lock(&philo->mutex[philo->next_fork]);
	print_message("has taken fork", philo);
	pthread_mutex_lock(&philo->lm_mutex);
	print_message("is eating", philo);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lm_mutex);
	ft_usleep(philo->tto_eat, philo);
	pthread_mutex_lock((philo->ag_mutex));
	if (*philo->all_good != -1)
		*(philo->all_good) += 1;
	else
		return (0);
	pthread_mutex_unlock((philo->ag_mutex));
	pthread_mutex_unlock(&philo->mutex[philo->next_fork]);
	pthread_mutex_unlock(&philo->mutex[philo->own_fork]);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)(arg);
	while (++i < philo->nb_eat || (philo->nb_eat == -1))
	{
		pthread_mutex_lock((philo->ag_mutex));
		if (*philo->all_good == -1)
			return (NULL);
		pthread_mutex_unlock((philo->ag_mutex));
		if (philo_eat(philo) == 0)
			return (NULL);
		print_message("is sleeping", philo);
		ft_usleep(philo->tto_sleep, philo);
		pthread_mutex_lock((philo->ag_mutex));
		if (*philo->all_good == -1)
			return (NULL);
		else
			print_message("is thinking", philo);
		pthread_mutex_unlock((philo->ag_mutex));
	}
	return (NULL);
}

void	start_half_thread(t_philo *philo, int i, int *all_good, time_t now)
{
	while (i < philo->nb_philo)
	{
		philo[i].last_meal = get_time();
		philo[i].ms = now;
		philo[i].all_good = all_good;
		pthread_create(&(philo[i].thread), NULL, routine, &philo[i]);
		pthread_detach(philo[i].thread);
		i += 2;
	}
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		i = -1;
		while (++i < philo->nb_philo)
		{
			pthread_mutex_lock((philo->ag_mutex));
			if (*philo->all_good == philo->nb_philo * philo->nb_eat)
				return (NULL);
			pthread_mutex_lock(&philo[i].lm_mutex);
			if (get_time() - philo[i].last_meal > philo->tto_die)
			{
				print_message("died", &philo[i]);
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

void	run_philo(t_philo *philo)
{
	time_t		now;
	pthread_t	thread;
	int			all_good;
	int			i;

	now = get_time();
	all_good = 0;
	start_half_thread(philo, 0, &all_good, now);
	ft_usleep(10, philo);
	start_half_thread(philo, 1, &all_good, now);
	pthread_create(&thread, NULL, monitor, philo);
	pthread_join(thread, NULL);
	i = -1;
	while (++i < philo->nb_philo)
		pthread_detach(philo[i].thread);
}
