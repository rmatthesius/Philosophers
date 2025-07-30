/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatthes <rmatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:49:25 by rmatthes          #+#    #+#             */
/*   Updated: 2024/09/20 12:49:25 by rmatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# ifndef PHIL_MAX
#  define PHIL_MAX 250
# endif

typedef struct s_programm	t_programm;

typedef struct s_philo
{
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_t		thread;
	size_t			meals_eaten;
	size_t			id;
	size_t			start_time;
	size_t			last_meal;
	bool			running;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*meal_lock;
	t_programm		*prog;
}	t_philo;

typedef struct s_programm
{
	size_t			nb_philos;
	size_t			meals_to_eat;
	size_t			time_to_die;
	bool			start_flag;
	bool			end;
	int				argc;
	pthread_t		monitor;
	t_philo			philos[PHIL_MAX];
	pthread_mutex_t	forks[PHIL_MAX];
	pthread_mutex_t	meal_locks[PHIL_MAX];
	pthread_mutex_t	stfu[1];
	pthread_mutex_t	switch_flag[1];
}	t_programm;

void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(size_t n);
size_t	get_time(void);
size_t	atosize_t(char *s);
void	print_meals_eaten_msg(t_programm *prog, t_philo *philo);
void	print_uptate(char *str, t_philo *philo);
void	print_dead_msg(t_philo *philo);
void	take_forks(t_philo *philo);
void	put_forks(t_philo *philo);
void	one_philo(t_philo *philo);
void	*philo_thread(void *arg);
void	*monitor_thread(void *arg);
int		meals_eaten(t_programm *prog);
int		is_dead(t_programm *prog);
int		is_nrunning(t_programm *prog);
int		is_running(t_programm *prog);
void	my_sleep(size_t time);
int		init_programm(t_programm *prog, int argc, char **argv);
int		init_philos(t_programm *prog, char **argv);
void	free_mutex_forks(t_programm *prog, int i);
#endif
