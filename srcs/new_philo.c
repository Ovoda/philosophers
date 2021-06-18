/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:05:11 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 14:03:36 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo *init_philo(t_table *table)
{
    t_philo *philo;
    int i;
    int last_meal;

    i = -1;
    philo = (t_philo *)malloc(sizeof(t_philo) * (table->nb_philo + 1));
    if (!philo)
        return (NULL);
    while (++i < table->nb_philo)
    {
        philo[i].id = i;
        philo[i].own_fork = i;
        philo[i].next_fork = i + 1;
        if (i + 1 >= table->nb_philo)
            philo[i].next_fork = 0;
        philo[i].nb_fork = table->nb_philo;
        gettimeofday(&philo[i].start, NULL);
        last_meal = philo[i].start.tv_sec * 1000 + philo[i].start.tv_usec / 1000;
        philo[i].last_meal = &last_meal;
    }
    return (philo);
}

void *death(void *arg)
{
    struct timeval current_time;
    int ms_curent_time;
    t_philo philo;

    philo = *(t_philo *)arg;
    while (1)
    {
        gettimeofday(&current_time, NULL);
        ms_curent_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
        if (ms_curent_time - *(philo.last_meal) <= 0)
            printf("last meal for 0 was %dms ago\n", ms_curent_time - *(philo.last_meal));
    }
}

void run_philo(t_philo *philo, pthread_mutex_t *mutex)
{
    int i;
    int begin;
    int ready;

    i = -1;
    begin = 0;
    ready = 0;
    while (++i < philo->nb_fork)
    {
        philo[i].begin = &begin;
        philo[i].ready = &ready;
        philo[i].mutex = mutex;
        pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]);
    }
    pthread_create(&philo[i].thread, NULL, death, (void *)&philo[0]);
    i = -1;
    while (++i <= philo->nb_fork)
        pthread_join(philo[i].thread, NULL);
}

int philo(t_table *table)
{
    t_philo *philo;
    pthread_mutex_t *mutex;

    philo = init_philo(table);
    mutex = init_mutex(table);
    run_philo(philo, mutex);
    destroy_mutex(philo, table);
    return (0);
}