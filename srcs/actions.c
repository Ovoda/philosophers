/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:51:19 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/19 14:19:01 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void philo_eat(t_philo *philo)
{
    int ms_start;
    
    pthread_mutex_lock(&philo->mutex[philo->own_fork]);
    print_message(*philo, ACTION_FORK);
    pthread_mutex_lock(&philo->mutex[philo->next_fork]);
    print_message(*philo, ACTION_FORK);

    if (ft_get_time(philo->ms_start) - philo->last_meal > philo->tto_die)
    {
        print_message(*philo, DEATH);
        *(philo->alive) = 0;
    }
    print_message(*philo, ACTION_EAT);
    philo->last_meal = ft_get_time(philo->ms_start);
    ft_usleep(philo->tto_eat);
    pthread_mutex_unlock(&philo->mutex[philo->own_fork]);
    pthread_mutex_unlock(&philo->mutex[philo->next_fork]);
}

void philo_sleep(t_philo *philo)
{
    print_message(*philo, ACTION_SLEEP);
    ft_usleep(philo->tto_sleep);
}

void philo_think(t_philo *philo)
{
    print_message(*philo, ACTION_THINK);
}