/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:56:40 by calide-n          #+#    #+#             */
/*   Updated: 2021/05/30 10:01:19 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int main(int argc, char **argv)
{
	t_table *table;

	table = handle_input(argc, argv);
	if (!table)
		return (ft_free_table(table, -1));
	print_table(*table);
	philo_one(table);
    return (ft_free_table(table, 0));
}