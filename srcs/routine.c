/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/21 12:46:41 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	sub_t(time_t ms)
{
	return (get_time() - ms);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)(arg);
	while (++i < philo->nb_eat || (philo->nb_eat == -1))
	{
		philo->all_good = 0;
		pthread_mutex_lock(&philo->mutex[philo->own_fork]);
		printf("%06ld %d has taken fork\n", sub_t(philo->ms), philo->id + 1);
		pthread_mutex_lock(&philo->mutex[philo->next_fork]);
		printf("%06ld %d has taken fork\n", sub_t(philo->ms), philo->id + 1);
		printf("%06ld %d is eating\n", sub_t(philo->ms), philo->id + 1);
		philo->last_meal = get_time();
		ft_usleep(philo->tto_eat);
		printf("%06ld %d is sleeping\n", sub_t(philo->ms), philo->id + 1);
		pthread_mutex_unlock(&philo->mutex[philo->next_fork]);
		pthread_mutex_unlock(&philo->mutex[philo->own_fork]);
		philo->all_good = 1;
		ft_usleep(philo->tto_sleep);
		printf("%06ld %d is thinking\n", sub_t(philo->ms), philo->id + 1);
	}
	philo->all_good = 1;
	return (NULL);
}

void	start_half_thread(t_philo *philo, int i, int *alive, time_t now)
{
	while (i < philo->nb_philo)
	{
		philo[i].last_meal = get_time();
		philo[i].ms = now;
		philo[i].alive = alive;
		pthread_create(&(philo[i].thread), NULL, routine, &philo[i]);
		pthread_detach(philo[i].thread);
		i += 2;
	}
}

int	check_if_all_good(t_philo *philo)
{
	int	i;
	int	all_good;

	i = -1;
	all_good = 0;
	while (++i < philo->nb_philo)
		if (philo[i].all_good == 1)
			all_good += 1;
	if (all_good >= philo->nb_philo - 1 && philo->nb_eat != -1)
		return (0);
	return (1);
}

void	run_philo(t_philo *philo)
{
	int		alive;
	int		i;
	time_t	now;

	alive = 1;
	now = get_time();
	start_half_thread(philo, 0, &alive, now);
	ft_usleep(philo->tto_eat - 10);
	start_half_thread(philo, 1, &alive, now);
	while (alive)
	{
		if (check_if_all_good(philo) == 0)
			return ;
		i = -1;
		while (++i < philo->nb_philo)
		{
			if (get_time() - philo[i].last_meal > philo->tto_die)
			{
				printf("%06ld %d died\n", sub_t(philo->ms), philo->id + 1);
				return ;
			}
		}
		usleep(1000);
	}
}
