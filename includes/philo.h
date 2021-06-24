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
# include <sys/time.h>
# include <pthread.h>
# define INT_MAX 2147483647
# define PHILO "./philo"
# define INPUT_ERROR 1
# define NB_ARG_ERROR "Wrong number of arguments"
# define NOT_PINT_ERROR "All arguments must be positive integers"
# define INPUT_ARG_1 "[number of philosopher]"
# define INPUT_ARG_2 "[time to die]"
# define INPUT_ARG_3 "[time to eat]"
# define INPUT_ARG_4 "[time to sleep]"
# define INPUT_ARG_5 "[number of time each philosopher must eat]"
# define ACTION_EAT "is eating\n"
# define ACTION_THINK "is thinking\n"
# define ACTION_SLEEP "is sleeping\n"
# define ACTION_FORK "has taken a fork\n"
# define DEATH "died\n"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*ag_mutex;
	pthread_mutex_t lm_mutex;
	pthread_mutex_t *av_mutex;
	long int		tto_eat;
	long int		tto_sleep;
	long int		tto_die;
	int				nb_eat;
	time_t			ms;
	int				nb_philo;
	int				own_fork;
	int				next_fork;
	long int		last_meal;
	int				*all_good;
	int				*alive;
}				t_philo;

typedef struct s_global
{
	int				nb_philo;
	long int		tto_die;
	long int		tto_eat;
	long int		tto_sleep;
	long int		ms;
	int				nb_eat;
	struct timeval	start;
}				t_global;

//Main functions
void			*routine(void *arg);
t_global		*handle_input(int argc, char **argv);
void			run_philo(t_philo *philo);

//Errors
void			*ft_null_error(char *str, int mode);

//Secondary functions (tools)
time_t			get_time(void);
int				is_int(char *str);
void			ft_usleep(int time, int *all_good);
int				ft_positive_atoi(char *str);
void			destroy_mutex(t_philo *philo);
pthread_mutex_t	*init_mutex(t_global *global);
int				ft_free_global(t_global *global, int ret);
t_global		*init_global(char **argv, t_global *global);
int				ft_isint_foreach(char **argv, int (*func)(char *));

#endif