/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 09:33:14 by calide-n          #+#    #+#             */
/*   Updated: 2021/05/30 10:03:35 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_global	*init_global(char **argv, t_global *global)
{
	global = (t_global *)malloc(sizeof(t_global));
	global->nb_philo = ft_positive_atoi(argv[1]);
	global->nb_forks = global->nb_philo;
	global->tto_die = ft_positive_atoi(argv[2]);
	global->tto_eat = ft_positive_atoi(argv[3]);
	global->tto_sleep = ft_positive_atoi(argv[4]);
	if (argv[5])
		global->nb_eat = ft_positive_atoi(argv[5]);
	else
		global->nb_eat = 0;
	if (global->nb_philo < 0 || global->tto_die < 0 || global->tto_sleep < 0
		|| global->tto_eat < 0 || global->nb_eat < 0)
		return (NULL);
	return (global);
}

void    print_global(t_global global)
{
	printf("global :\n");
	printf("Nb of philo : %d\n", global.nb_philo);
	printf("Time to die : %d\n", global.tto_die);
	printf("Tiem to eat : %d\n", global.tto_eat);
	printf("Time to sleep : %d\n", global.tto_sleep);
	if (global.nb_eat != 0)
		printf("Nb of time each philo must eat : %d\n", global.nb_eat);
	else
		printf("Nb of time each philo must eat : Default value (infinite)\n");
}

int ft_free_global(t_global *global, int ret)
{
	free(global);
	return (ret);
}
