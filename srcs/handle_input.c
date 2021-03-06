/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 08:42:05 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/24 14:32:36 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_null_error(char *str, int mode)
{
	printf("Error: %s\n", str);
	if (mode == INPUT_ERROR)
		printf("%s %s %s %s %s %s\n", PHILO, INPUT_ARG_1, INPUT_ARG_2,
			INPUT_ARG_3, INPUT_ARG_4, INPUT_ARG_5);
	return (NULL);
}

t_global	*handle_input(int argc, char **argv)
{
	t_global	*global;

	global = NULL;
	if (argc < 5 || argc > 6)
		return (ft_null_error(NB_ARG_ERROR, INPUT_ERROR));
	if (ft_isint_foreach(argv, &is_int) < 0)
		return (ft_null_error(NOT_PINT_ERROR, INPUT_ERROR));
	global = init_global(argv, global);
	if (global == NULL)
		return (ft_null_error(NOT_PINT_ERROR, INPUT_ERROR));
	return (global);
}

t_global	*init_global(char **argv, t_global *global)
{
	global = (t_global *)malloc(sizeof(t_global));
	global->nb_philo = ft_positive_atoi(argv[1]);
	global->tto_die = ft_positive_atoi(argv[2]);
	global->tto_eat = ft_positive_atoi(argv[3]);
	global->tto_sleep = ft_positive_atoi(argv[4]);
	if (argv[5])
		global->nb_eat = ft_positive_atoi(argv[5]);
	else
		global->nb_eat = -1;
	if (global->nb_philo < 0 || global->tto_die < 0 || global->tto_sleep < 0
		|| global->tto_eat < 0 || global->nb_eat < -1)
		return (NULL);
	return (global);
}

int	ft_free_global(t_global *global, int ret)
{
	free(global);
	return (ret);
}
