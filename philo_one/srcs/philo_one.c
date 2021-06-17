/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 10:01:59 by calide-n          #+#    #+#             */
/*   Updated: 2021/05/30 11:38:17 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void    *show_thread(void *arg)
{
	static int	prev_id = 4;
	int			id;

	id = ((t_philo *)arg)->id;
	//printf("id -> %d, prev -> %d\n", id, prev_id);

	if ((id == 1 && prev_id == 4) || (prev_id == id - 1))
	{
		pthread_mutex_lock(&mutex);
		printf("I am philo [%d] and I took the fork from philo [%d]\n", id, prev_id);
		prev_id = ((t_philo *)arg)->id;
		usleep(200);
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

void    create_philo(t_table table)
{
	int			i;
	t_philo		*philos;

	i = 0;
	printf("nb_philo %d\n", table.nb_philo);
	philos = (t_philo *)malloc(sizeof(t_philo) * table.nb_philo);
	while (1)
	{
		if (i >= 4)
			i = 0;
		philos[i].id = i + 1;
		philos[i].eat_time = table.tto_eat;
		philos[i].die_in = table.tto_die;
		philos[i].sleep_time = table.tto_sleep;
		pthread_create(&(philos[i].thread), NULL, &show_thread, (void *)&philos[i]);
		i++;
	}
	i = -1;
	while (++i < table.nb_philo)
		pthread_join(philos[i].thread, NULL);
}

int philo_one(t_table *table)
{
	create_philo(*table);
	return (0);
}