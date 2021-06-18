/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:51:19 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 14:02:40 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    philo_eat(t_philo philo)
{   
    struct timeval  start;
    int             ms_start;

    pthread_mutex_lock(&philo.mutex[philo.own_fork]);
    print_message(philo, ACTION_FORK);
    pthread_mutex_lock(&philo.mutex[philo.next_fork]);
    print_message(philo, ACTION_FORK);
    print_message(philo, ACTION_EAT);
    ft_usleep(100);
    gettimeofday(&start, NULL);
    *(philo.last_meal) = start.tv_sec * 1000 + start.tv_usec / 1000;
}

void    philo_sleep(t_philo philo)
{
    print_message(philo, ACTION_SLEEP);
    pthread_mutex_unlock(&philo.mutex[philo.own_fork]);
    pthread_mutex_unlock(&philo.mutex[philo.next_fork]);
    ft_usleep(100);
}

void    philo_think(t_philo philo)
{
    print_message(philo, ACTION_THINK);
    ft_usleep(100);
}