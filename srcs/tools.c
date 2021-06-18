/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 09:28:09 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 13:22:07 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_message(t_philo philo, char *action)
{
	struct timeval	stop;
	int	ms_stop;
	int	ms_start;
	int	time;

	gettimeofday(&stop, NULL);
	ms_stop = stop.tv_sec * 1000 + stop.tv_usec / 1000;
	ms_start = philo.start.tv_sec * 1000 + philo.start.tv_usec / 1000;
	printf("%d %d %s\n", ms_stop - ms_start, philo.id, action);
}

int    ft_usleep(int time)
{
    struct timeval start;

    int ms_start;
    int ms_stop;
    gettimeofday(&start, NULL);
    ms_start = start.tv_sec * 1000 + start.tv_usec / 1000;
    ms_stop = ms_start + time;
    while (ms_start < ms_stop)
    {
        gettimeofday(&start, NULL);
        ms_start = start.tv_sec * 1000 + start.tv_usec / 1000;
    }
    return (time);
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