/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:51:19 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/19 11:28:58 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void philo_eat(t_params *params)
{
    struct timeval start;
    int ms_start;
    t_philo philo;

    philo = params->global->philo[params->i];
    pthread_mutex_lock(&philo.mutex[philo.own_fork]);
    print_message(params, ACTION_FORK);
    pthread_mutex_lock(&philo.mutex[philo.next_fork]);
    print_message(params, ACTION_FORK);
    print_message(params, ACTION_EAT);
    ft_usleep(params->global->tto_eat);
    gettimeofday(&start, NULL);
}

void philo_sleep(t_params *params)
{
    t_philo philo;

    philo = params->global->philo[params->i];
    print_message(params, ACTION_SLEEP);
    pthread_mutex_unlock(&philo.mutex[philo.own_fork]);
    pthread_mutex_unlock(&philo.mutex[philo.next_fork]);
    ft_usleep(params->global->tto_sleep);
}

void philo_think(t_params *params)
{
    t_philo philo;

    philo = params->global->philo[params->i];
    print_message(params, ACTION_THINK);
}