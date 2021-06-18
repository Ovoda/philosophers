/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 08:42:05 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 21:58:24 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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