/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 08:42:05 by calide-n          #+#    #+#             */
/*   Updated: 2021/05/30 09:56:28 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_table	*handle_input(int argc, char **argv)
{
	t_table	*table;
	
	table = NULL;
	if (argc < 5 || argc > 6)
		return (ft_null_error(NB_ARG_ERROR, INPUT_ERROR));
	if (ft_isint_foreach(argv, &is_int) < 0)
		return (ft_null_error(NOT_PINT_ERROR, INPUT_ERROR));
	table = init_table(argv, table);
	if (table == NULL)
		return (ft_null_error(NOT_PINT_ERROR, INPUT_ERROR));
	return (table);
}