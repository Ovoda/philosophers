/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:05:11 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/20 16:09:13 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philo(t_global *global, pthread_mutex_t *mutex)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * (global->nb_philo));
	if (!philo)
		return (NULL);
	while (++i < global->nb_philo)
	{
		philo[i].id = i;
		philo[i].nb_eat = global->nb_eat;
		philo[i].own_fork = i;
		philo[i].all_good = 0;
		philo[i].next_fork = i - 1;
		if (i - 1 < 0)
			philo[i].next_fork = global->nb_philo - 1;
		philo[i].nb_philo = global->nb_philo;
		philo[i].ms = global->ms;
		philo[i].tto_eat = global->tto_eat;
		philo[i].tto_die = global->tto_die;
		philo[i].tto_sleep = global->tto_sleep;
		philo[i].mutex = mutex;
	}
	return (philo);
}

pthread_mutex_t	*init_mutex(t_global *global)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = -1;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* global->nb_philo);
	while (++i < global->nb_philo)
		pthread_mutex_init(&mutex[i], NULL);
	return (mutex);
}

int	main(int argc, char **argv)
{
	t_global		*global;
	pthread_mutex_t	*mutex;
	t_philo			*philo;
	int				i;

	global = handle_input(argc, argv);
	if (!global)
		return (ft_free_global(global, -1));
	i = -1;
	mutex = init_mutex(global);
	philo = init_philo(global, mutex);
	run_philo(philo);
	i = -1;
	while (++i < philo->nb_philo)
		pthread_mutex_destroy(&philo[0].mutex[i]);
	free(philo);
	free(mutex);
	free(global);
	return (0);
}
