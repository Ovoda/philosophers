/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:27:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 15:14:07 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *routine(void *arg)
{
    t_philo *philo;
    int     i = 0;
    int     begin;

    philo = (t_philo *)arg;
    begin = 0;
    while (++i < 10)
    {
        if (begin == 0 && philo->id % 2 != 0)
        {
            ft_usleep(10);
            begin = 1;
        }
        philo_eat(*philo);
        philo_sleep(*philo);
        philo_think(*philo);
    }
    return (NULL);
}