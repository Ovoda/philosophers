/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:05:11 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/20 13:04:49 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo *init_philo(t_global *global)
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
        philo[i].own_fork = i;
        philo[i].next_fork = i - 1;
        if (i - 1 < 0)
            philo[i].next_fork = global->nb_philo - 1;
        philo[i].nb_fork = global->nb_philo;
        philo[i].ms_start = global->ms_start;
        philo[i].tto_eat = global->tto_eat;
        philo[i].tto_die = global->tto_die;
        philo[i].tto_sleep = global->tto_sleep;
    }
    return (philo);
}

void run_philo(t_global *global, pthread_mutex_t *mutex)
{
    t_philo *philo;
    int alive;
    int i;

    i = -1;
    philo = global->philo;
    alive = 1;
    while (++i < global->nb_philo)
    {
        philo[i].mutex = mutex;
        philo[i].alive = &alive;
    }
    i = 0;
    time_t now;
    now = get_time();
    while (i < global->nb_philo)
    {
        philo[i].last_meal = get_time();
        philo[i].ms_start = now;
        pthread_create(&(philo[i].thread), NULL, routine, &philo[i]);
        pthread_detach(philo[i].thread);
        i += 2;
    }
    usleep(100);
    i = 1;
    while (i < global->nb_philo)
    {
        philo[i].last_meal = get_time();
        philo[i].ms_start = now;
        pthread_create(&(philo[i].thread), NULL, routine, &philo[i]);
        pthread_detach(philo[i].thread);
        i += 2;
    }
    while (alive)
    {
        i = -1;
        while (++i < global->nb_philo)
        {
            if (ft_get_time(philo->ms_start) - philo[i].last_meal > global->tto_die)
            {
                printf("%d died\n", philo[i].id);
                return;
            }
        }
        usleep(1000);
    }
    //i = -1;
    //while (++i < global->nb_philo)
    //    pthread_detach(philo[i].thread);
}

int philo(t_global *global)
{
    pthread_mutex_t *mutex;

    global->philo = init_philo(global);
    mutex = init_mutex(global);
    run_philo(global, mutex);
    destroy_mutex(global->philo, global);
    return (0);
}