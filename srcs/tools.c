/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 09:28:09 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/20 14:57:10 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isint_foreach(char **argv, int (*func)(char *))
{
	int	i;

	i = 0;
	while (argv[++i])
		if (func(argv[i]) < 0)
			return (-1);
	return (0);
}

int	is_int(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (-1);
	return (0);
}

int	ft_positive_atoi(char *str)
{
	long int	n;
	int			i;

	n = 0;
	i = -1;
	while (str[++i])
		n = n * 10 + (str[i] - 48);
	if (n > INT_MAX)
		return (-1);
	return ((int)n);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int time, t_philo *philo)
{
	time_t	ms_stop;
	time_t	ms;

	ms = get_time();
	ms_stop = ms + time;
	while (get_time() < ms_stop)
	{
		pthread_mutex_lock(philo->ag_mutex);
			if (*philo->all_good == -1)
				return ;
		pthread_mutex_unlock(philo->ag_mutex);
		usleep(100);
	}
}
