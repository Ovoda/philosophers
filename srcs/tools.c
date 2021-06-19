/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 09:28:09 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/19 15:13:35 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_message(t_philo philo, char *action)
{
	struct timeval	stop;
	int	ms_stop;
	int	time;
	int	len;

	len = 0;
	gettimeofday(&stop, NULL);
	ms_stop = stop.tv_sec * 1000 + stop.tv_usec / 1000;
	while (action[len])
		len++;
	printf("%05d %d %s", ms_stop - philo.ms_start, philo.id, action);
}

int ft_isint_foreach(char **argv, int (*func)(char *))
{
	int i;

	i = 0;
	while (argv[++i])
		if (func(argv[i]) < 0)
			return (-1);
	return (0);
}

int is_int(char *str)
{
	int i;

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