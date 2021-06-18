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

int main ()
{
    struct timeval  start;
    struct timeval  stop;

    int ms_start;
    int ms_stop;
    while (1)
    {
        gettimeofday(&start, NULL);
        ft_usleep(10);
        gettimeofday(&stop, NULL);
        ms_start = start.tv_sec * 1000 + start.tv_usec / 1000;
        ms_stop = stop.tv_sec * 1000 + stop.tv_usec / 1000;
        printf("%d - %d = %d\n", ms_start, ms_stop, ms_stop - ms_start);
    }
    return (0);
}