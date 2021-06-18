/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:56:40 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/18 21:58:24 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char **argv)
{
	t_global *global;

	global = handle_input(argc, argv);
	if (!global)
		return (ft_free_global(global, -1));
	print_global(*global);
	philo(global);
    return (0);
}