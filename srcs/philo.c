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

#include "../includes/philo.h"

void *exec1(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	struct timeval current_time;
	long int time;

	int	fork = 0;
	int	f1;
	int	f2;
	//while (1)
	//{
		while (pthread_mutex_lock(&philo.mutex[fork]) != 0)
			fork++;
		printf("philo %d has taken fork %d\n", philo.id, fork);
		f1 = fork;
		fork++;
		while (pthread_mutex_lock(&philo.mutex[fork]) != 0)
			fork++;
		printf("philo %d has taken fork %d\n", philo.id, fork);
		f2 = fork;
		gettimeofday(&current_time, NULL);
		printf("philo %d is eating\n", philo.id);
		sleep(1);
		pthread_mutex_unlock(&philo.mutex[f1]);
		pthread_mutex_unlock(&philo.mutex[f2]);
		gettimeofday(&current_time, NULL);
		printf("philo %d is sleeping\n", philo.id);
		usleep(10000);
		gettimeofday(&current_time, NULL);
		//printf("%05d philo %d is thinking\n", (current_time.tv_usec - philo.start.tv_usec) / 1, philo.id);
		usleep(10000);
	//}
	return (NULL);
}

void create_philo(t_table *table)
{
	t_philo	*p;
	int		i;
	pthread_mutex_t *mutex;

	i = -1;
	p = (t_philo *)malloc(sizeof(t_philo) * table->nb_philo);
	mutex = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!p)
		return ;
	while (++i < table->nb_philo)
		pthread_mutex_init(&mutex[i], NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		p[i].id = i;	
		gettimeofday(&(p[i].start), NULL);
		p[i].mutex = mutex;
		pthread_create(&p[i].thread, NULL, exec1, (void *)&(p[i]));
	}
	i = -1;
	while (++i < table->nb_philo)
		pthread_join(p[i].thread, NULL);
	pthread_mutex_destroy(&mutex[0]);
	pthread_mutex_destroy(&mutex[1]);
}

int philo(t_table *table)
{
	create_philo(table);
	return (0);
}