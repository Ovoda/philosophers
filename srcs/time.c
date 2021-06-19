/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:37:37 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/19 14:39:12 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned int    ft_get_current_time(void)
{
    struct timeval  time;
    unsigned long   ms_time;

    gettimeofday(&time, NULL);
    ms_time = time.tv_sec * 1000 + time.tv_usec / 1000;
    return (ms_time);
}

int    ft_usleep(int time)
{
    unsigned long ms_stop;
    
    ms_stop = ft_get_current_time() + time;
    while (ft_get_current_time() < ms_stop)
        usleep(100);
    return (time);
}

int     ft_get_time(int ms_start)
{
    struct timeval  current_time;
    int             ms_current_time;
    
    gettimeofday(&current_time, NULL);
    ms_current_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    return (ms_current_time - ms_start);
}