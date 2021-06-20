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
# define ACTION_EAT "is eating\n"
# define ACTION_THINK "is thinking\n"
# define ACTION_SLEEP "is sleeping\n"
# define ACTION_FORK "has taken a fork\n"
# define DEATH "died\n"

typedef struct	s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t *mutex;
	long int		tto_eat;
	long int		tto_sleep;
	long int		tto_die;
	int				nb_eat;
	time_t			ms_start;
	int				nb_philo;
	int				own_fork;
	int				next_fork;
	long int		last_meal;
	int				all_good;
	int				*alive;
}				t_philo;

typedef struct  s_global 
{
	int				nb_philo;
	long int		tto_die;
	long int		tto_eat;
	long int		tto_sleep;
	long int		ms_start;
	int				nb_eat;
	struct timeval	start;
}				t_global;

typedef struct	s_params
{
	int			i;
	t_global	*global;
}				t_params;

t_global	*handle_input(int argc, char **argv);
int			philo(t_global *global);
void		*routine(void *arg);

//ERRORS
void		*ft_null_error(char *str, int mode);

//TOOLS
int			ft_isint_foreach(char **argv, int (*func)(char *));
int			is_int(char *str);
int			ft_positive_atoi(char *str);

//TIME TOOLS
int			ft_usleep(int time);
long int	ft_get_time(long int ms_start);
time_t		get_time(void);

//MUTEX TOOLS
void				destroy_mutex(t_philo *philo);
pthread_mutex_t    *init_mutex(t_global *global);

//global TOOLS
void	print_global(t_global global);
int		ft_free_global(t_global *global, int ret);
t_global	*init_global(char **argv, t_global *global);

#endif