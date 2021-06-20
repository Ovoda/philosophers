/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 09:28:09 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/20 14:15:25 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int ft_positive_atoi(char *str)
{
	long int n;
	int i;

	n = 0;
	i = -1;
	while (str[++i])
		n = n * 10 + (str[i] - 48);
	if (n > INT_MAX)
		return (-1);
	return ((int)n);
}