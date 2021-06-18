/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 13:27:31 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void start_routine(t_philo philo)
{
    philo_eat(philo);
    philo_sleep(philo);
    philo_think(philo);
    *(philo.ready) += 1;
    if (*(philo.ready) == philo.nb_fork / 2 || *(philo.ready) == (philo.nb_fork / 2) + 1)
        *(philo.begin) = 1;
}

void *routine(void *arg)
{
    t_philo philo;

    philo = *(t_philo *)arg;
    while (1)
    {
        if (philo.id % 2 != 0)
            ft_usleep(10);
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}