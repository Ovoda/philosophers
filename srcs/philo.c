/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 10:01:59 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 12:34:25 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	increment_fork(int fork, int fork_nb)
{
	if (fork < fork_nb - 1)
		return (fork + 1);
	return (0);
}

int	chrono(struct timeval start, struct timeval stop)
{
	return ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}

void *exec1(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	struct timeval current_time;
	long int time;

	int	fork = 0;
	int	f1;
	int	f2;
	while (1)
	{
		if (*(philo.begin) == 0 && (philo.id % 2 == 0))
		{
			printf("ENTER philo %d begin %d, id %d, ready %d\n", philo.id, *(philo.begin), philo.id, *(philo.ready));
			pthread_mutex_lock(&philo.mutex[philo.own_fork]);
			gettimeofday(&current_time, NULL);
			printf("%ld philo %d has taken fork %d\n", current_time.tv_sec, philo.id, philo.own_fork);

			pthread_mutex_lock(&philo.mutex[philo.next_fork]);
			gettimeofday(&current_time, NULL);
			printf("%ld %d philo %d has taken fork %d\n", current_time.tv_sec, current_time.tv_usec, philo.id, philo.next_fork);
			gettimeofday(&current_time, NULL);
			printf("%ld %d philo %d is eating\n", current_time.tv_sec, current_time.tv_usec, philo.id);
			sleep(1);
			gettimeofday(&current_time, NULL);
			printf("%ld %d philo %d is sleeping\n", current_time.tv_sec, current_time.tv_usec, philo.id);
			pthread_mutex_unlock(&philo.mutex[philo.own_fork]);
			pthread_mutex_unlock(&philo.mutex[philo.next_fork]);
			sleep(1);
			gettimeofday(&current_time, NULL);
			//printf("%05d philo %d is thinking\n", (current_time.tv_usec - philo.start.tv_usec) / 1, philo.id);
			sleep(1);
			*(philo.last_meal) = 
			*(philo.ready) += 1;
			if (*(philo.ready) == philo.nb_fork / 2 || *(philo.ready) == (philo.nb_fork / 2) + 1)
				*(philo.begin) = 1;
		}
		else if (*(philo.begin) == 1)
		{
			pthread_mutex_lock(&philo.mutex[philo.own_fork]);
			gettimeofday(&current_time, NULL);
			printf("%ld %d philo %d has taken fork %d\n", current_time.tv_sec, current_time.tv_usec, philo.id, philo.own_fork);

			pthread_mutex_lock(&philo.mutex[philo.next_fork]);
			gettimeofday(&current_time, NULL);
			printf("%ld %d philo %d has taken fork %d\n", current_time.tv_sec, current_time.tv_usec, philo.id, philo.next_fork);
			gettimeofday(&current_time, NULL);
			printf("%ld %d philo %d is eating\n", current_time.tv_sec, current_time.tv_usec, philo.id);
			sleep(1);
			gettimeofday(&current_time, NULL);
			printf("%ld %d philo %d is sleeping\n", current_time.tv_sec, current_time.tv_usec, philo.id);
			pthread_mutex_unlock(&philo.mutex[philo.own_fork]);
			pthread_mutex_unlock(&philo.mutex[philo.next_fork]);
			sleep(1);
			gettimeofday(&current_time, NULL);
			//printf("%05d philo %d is thinking\n", (current_time.tv_usec - philo.start.tv_usec) / 1, philo.id);
			sleep(1);
		}
	}
	return (NULL);
}

void create_philo(t_table *table)
{
	t_philo	*p;
	int		i;
	pthread_mutex_t *mutex;
	int		fork;
	int		begin;
	int		ready;

	i = -1;
	fork = 0;
	begin = 0;
	ready = 0;
	p = (t_philo *)malloc(sizeof(t_philo) * table->nb_philo);
	mutex = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!p)
		return ;
	while (++i < table->nb_philo)
		pthread_mutex_init(&mutex[i], NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		p[i].mutex = mutex;
		(p[i].fork) = &fork;
		p[i].own_fork = i;
		p[i].begin = &begin;
		p[i].ready = &ready;
		p[i].next_fork = i + 1;
		if (p[i].next_fork >= table->nb_philo)
			p[i].next_fork = 0;
		p[i].nb_fork = table->nb_philo;
		pthread_create(&p[i].thread, NULL, exec1, (void *)&(p[i]));
	}
	i = -1;
	while (++i < table->nb_philo)
		pthread_join(p[i].thread, NULL);
}

int philo(t_table *table)
{
	create_philo(table);
	return (0);
}