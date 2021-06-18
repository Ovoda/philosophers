/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calide-n <calide-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:12:07 by calide-n          #+#    #+#             */
/*   Updated: 2021/05/30 11:20:36 by calide-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/time.h>
# include <pthread.h>
# define PHILO_ONE "./philo_one"
# define INPUT_ERROR 1
# define NB_ARG_ERROR "Wrong number of arguments"
# define NOT_PINT_ERROR "All arguments must be positive integers (0 < n < INT_MAX)"
# define INPUT_ARG_1 "[number of philosopher]"
# define INPUT_ARG_2 "[time to die]"
# define INPUT_ARG_3 "[time to eat]"
# define INPUT_ARG_4 "[time to sleep]"
# define INPUT_ARG_5 "[number of time each philosopher must eat]"
# define INT_MAX 2147483647
# define ACTION_EAT "is eating"
# define ACTION_THINK "is thinking"
# define ACTION_SLEEP "is sleeping"
# define ACTION_FORK "has taken a fork"

typedef struct	s_philo
{
	pthread_t		thread;
	int				id;
	int				sleep_time;
	int				eat_time;
	int				ms_start;
	struct timeval	start;
	pthread_mutex_t *mutex;
	int				*fork;
	int				nb_fork;
	int				own_fork;
	int				next_fork;
	int				*last_meal;
}				t_philo;

typedef struct  s_table 
{
	int				nb_forks;
	int				nb_philo;
	int				tto_die;
	int				tto_eat;
	int				tto_sleep;
	int				nb_eat;
}               t_table;


t_table	*handle_input(int argc, char **argv);
int		philo(t_table *table);
void	*routine(void *arg);

//ERRORS
void	*ft_null_error(char *str, int mode);

//TOOLS
int 	ft_isint_foreach(char **argv, int (*func)(char *));
int 	is_int(char *str);
int		ft_positive_atoi(char *str);
int		ft_usleep(int time);
void	print_message(t_philo philo, char *action);

//MUTEX TOOLS
void				destroy_mutex(t_philo *philo, t_table *table);
pthread_mutex_t    *init_mutex(t_table *table);

//TABLE TOOLS
void	print_table(t_table table);
int		ft_free_table(t_table *table, int ret);
t_table	*init_table(char **argv, t_table *table);

//ACTIONS
void    philo_eat(t_philo philo);
void    philo_sleep(t_philo philo);
void    philo_think(t_philo philo);

#endif