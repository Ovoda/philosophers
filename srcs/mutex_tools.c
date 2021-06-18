/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:24:14 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 13:14:57 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    destroy_mutex(t_philo *philo, t_table *table)
{
    int i;

    i = -1;
    while (++i < table->nb_philo)
        pthread_mutex_destroy(&philo->mutex[i]);
}

pthread_mutex_t *init_mutex(t_table *table)
{
    int i;
    pthread_mutex_t *mutex;

    i = -1;
    mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->nb_philo);
    while (++i < table->nb_philo)
        pthread_mutex_init(&mutex[i], NULL);
    return (mutex);
}