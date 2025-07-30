/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatthes <rmatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:49:10 by rmatthes          #+#    #+#             */
/*   Updated: 2025/07/30 13:17:16 by rmatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_running(t_programm *prog)
{
	size_t	i;

	i = 0;
	while (i < prog->nb_philos)
	{
		pthread_mutex_lock(prog->switch_flag);
		if (prog->philos[i].running == false)
			return (pthread_mutex_unlock(prog->switch_flag), 1);
		pthread_mutex_unlock(prog->switch_flag);
		i++;
	}
	return (0);
}

int	is_nrunning(t_programm *prog)
{
	size_t	i;

	i = 0;
	while (i < prog->nb_philos)
	{
		pthread_mutex_lock(prog->switch_flag);
		if (prog->philos[i].running == true)
			return (pthread_mutex_unlock(prog->switch_flag), 1);
		i++;
		pthread_mutex_unlock(prog->switch_flag);
	}
	return (0);
}

int	is_dead(t_programm *prog)
{
	size_t	i;

	i = 0;
	while (i < prog->nb_philos)
	{
		pthread_mutex_lock(prog->philos[i].meal_lock);
		if (prog->philos[i].last_meal == 0)
		{
			if (get_time() - prog->philos[i].start_time >= prog->time_to_die)
				return (print_dead_msg(&prog->philos[i]), 0);
		}
		else
		{
			if (get_time() - prog->philos[i].last_meal >= prog->time_to_die)
				return (print_dead_msg(&prog->philos[i]), 0);
		}
		pthread_mutex_unlock(prog->philos[i].meal_lock);
		i++;
	}
	return (1);
}

int	meals_eaten(t_programm *prog)
{
	size_t	i;
	bool	flag;

	i = 0;
	flag = false;
	if (prog->argc != 6)
		return (1);
	while (i < prog->nb_philos)
	{
		pthread_mutex_lock(prog->switch_flag);
		if (prog->philos[i].meals_eaten >= prog->meals_to_eat)
			flag = true;
		else
		{
			flag = false;
			pthread_mutex_unlock(prog->switch_flag);
			break ;
		}
		pthread_mutex_unlock(prog->switch_flag);
		i++;
	}
	if (flag)
		return (0);
	return (1);
}

void	*monitor_thread(void *arg)
{
	t_programm	*prog;

	prog = (t_programm *)arg;
	pthread_mutex_lock(prog->switch_flag);
	prog->start_flag = true;
	pthread_mutex_unlock(prog->switch_flag);
	if (prog->nb_philos != 1)
	{
		while (is_running(prog) != 0)
			usleep(1);
	}
	else
		usleep(1000);
	while (1)
	{
		if (is_dead(prog) == 0 || meals_eaten(prog) == 0)
		{
			prog->end = true;
			break ;
		}
	}
	while (is_nrunning(prog) != 0)
		usleep(1);
	return (NULL);
}
