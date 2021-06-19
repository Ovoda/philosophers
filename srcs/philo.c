/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:05:11 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/19 15:14:38 by calide-n         ###   ########.fr       */
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
    int i;
    pthread_t thread;
    t_philo *philo;
    t_params *params;
    int *last_meal;
    int alive;

    i = -1;
    philo = global->philo;
    alive = 1;
    params = malloc(sizeof(t_params) * global->nb_philo);
    last_meal = malloc(sizeof(int) * global->nb_philo);
    while (++i < global->nb_philo)
    {
        last_meal[i] = 0;
        philo[i].mutex = mutex;
        philo[i].last_meal = 0;
        philo[i].alive = &alive;
    }
    i = -1;
    gettimeofday(&global->start, NULL);
    global->ms_start = global->start.tv_sec * 1000 + global->start.tv_usec / 1000;
    while (++i < global->nb_philo)
    {
        last_meal[i] = 0;
        philo[i].mutex = mutex;
        philo[i].last_meal = 0;
        philo[i].ms_start = global->ms_start;
        pthread_create(&(philo[i].thread), NULL, routine, &philo[i]);
    }
    while (alive)
        usleep(100);
    i = -1;
    while (++i < global->nb_philo)
        pthread_detach(philo[i].thread);
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