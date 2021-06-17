/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 08:45:55 by calide-n          #+#    #+#             */
/*   Updated: 2021/05/30 09:49:51 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void *ft_null_error(char *str, int mode)
{
    printf("Error: %s\n", str);
    if (mode == INPUT_ERROR)
        printf("%s %s %s %s %s %s\n", PHILO_ONE, INPUT_ARG_1, INPUT_ARG_2,
        INPUT_ARG_3, INPUT_ARG_4, INPUT_ARG_5);
    return (NULL);
}