/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 09:33:14 by calide-n          #+#    #+#             */
/*   Updated: 2021/05/30 10:03:35 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_table	*init_table(char **argv, t_table *table)
{
	table = (t_table *)malloc(sizeof(t_table));
	table->nb_philo = ft_positive_atoi(argv[1]);
	table->nb_forks = table->nb_philo;
	table->tto_die = ft_positive_atoi(argv[2]);
	table->tto_eat = ft_positive_atoi(argv[3]);
	table->tto_sleep = ft_positive_atoi(argv[4]);
	if (argv[5])
		table->nb_eat = ft_positive_atoi(argv[5]);
	else
		table->nb_eat = 0;
	if (table->nb_philo < 0 || table->tto_die < 0 || table->tto_sleep < 0
		|| table->tto_eat < 0 || table->nb_eat < 0)
		return (NULL);
	return (table);
}

void    print_table(t_table table)
{
	printf("TABLE :\n");
	printf("Nb of philo : %d\n", table.nb_philo);
	printf("Time to die : %d\n", table.tto_die);
	printf("Tiem to eat : %d\n", table.tto_eat);
	printf("Time to sleep : %d\n", table.tto_sleep);
	if (table.nb_eat != 0)
		printf("Nb of time each philo must eat : %d\n", table.nb_eat);
	else
		printf("Nb of time each philo must eat : Default value (infinite)\n");
}

int ft_free_table(t_table *table, int ret)
{
	free(table);
	return (ret);
}
