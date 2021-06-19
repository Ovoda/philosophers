/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:37:37 by calide-n          #+#    #+#             */
/*   Updated: 2021/06/19 13:28:59 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int    ft_usleep(int time)
{
    struct timeval start;

    int ms_start;
    int ms_stop;
    gettimeofday(&start, NULL);
    ms_start = start.tv_sec * 1000 + start.tv_usec / 1000;
    ms_stop = ms_start + time;
    while (ms_start < ms_stop)
    {
        gettimeofday(&start, NULL);
        ms_start = start.tv_sec * 1000 + start.tv_usec / 1000;
    }
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