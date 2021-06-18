/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:05:11 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 22:09:41 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo *init_philo(t_global *global)
{
    t_philo *philo;
    int i;

    i = -1;
    philo = (t_philo *)malloc(sizeof(t_philo) * (global->nb_philo + 1));
    if (!philo)
        return (NULL);
    while (++i < global->nb_philo)
    {
        philo[i].id = i;
        philo[i].own_fork = i;
        philo[i].next_fork = i + 1;
        if (i + 1 >= global->nb_philo)
            philo[i].next_fork = 0;
        philo[i].nb_fork = global->nb_philo;
        gettimeofday(&philo[i].start, NULL);
        philo[i].ms_start = philo[i].start.tv_sec * 1000 + philo[i].start.tv_usec / 1000;
    }
    return (philo);
}

void run_philo(t_global *global, pthread_mutex_t *mutex)
{
    int i;
    pthread_t   thread;
    t_philo     *philo;
    t_params    params;

    i = -1;
    philo = global->philo;
    global->alive = 0;
    while (++i < philo->nb_fork)
    {
        philo[i].mutex = mutex;
        philo[i].last_meal = 200;
        params.global = global;
        params.i = i;
        pthread_create(&(philo[i].thread), NULL, routine, (void *)&(params));
    }
    //pthread_create(&thread, NULL, death, (void *)&philo);
    i = -1;
    while (++i < philo->nb_fork)
        pthread_join(philo[i].thread, NULL);
}

int philo(t_global *global)
{
    t_philo         *philo;
    pthread_mutex_t *mutex;

    philo = init_philo(global);
    mutex = init_mutex(global);
    run_philo(philo, mutex);
    destroy_mutex(philo, global);
    return (0);
}