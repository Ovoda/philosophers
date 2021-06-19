/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:05:11 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/19 11:02:43 by calide-n         ###   ########.fr       */
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
        philo[i].next_fork = i - 1;
        if (i - 1 < 0)
            philo[i].next_fork = global->nb_philo - 1;
        philo[i].nb_fork = global->nb_philo;
        gettimeofday(&global->start, NULL);
        global->ms_start = global->start.tv_sec * 1000 + global->start.tv_usec / 1000;
    }
    return (philo);
}

void run_philo(t_global *global, pthread_mutex_t *mutex)
{
    int i;
    pthread_t   thread;
    t_philo     *philo;
    t_params    *params;

    i = -1;
    philo = global->philo;
    global->alive = 0;
    params = malloc(sizeof(t_params) * global->nb_philo);
    printf("%d\n", global->nb_philo);
    while (++i < global->nb_philo)
    {
        philo[i].mutex = mutex;
        philo[i].last_meal = 200;
        params[i].global = global;
        params[i].i = i;
        pthread_create(&(philo[i].thread), NULL, routine, &params[i]);
    }
    //pthread_create(&thread, NULL, death, (void *)&philo);
    i = -1;
    while (++i < global->nb_philo)
        pthread_join(philo[i].thread, NULL);
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