/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatthes <rmatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:49:20 by rmatthes          #+#    #+#             */
/*   Updated: 2025/07/30 13:17:21 by rmatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_sleep(size_t time)
{
	size_t	new_time;

	new_time = get_time();
	while (get_time() - new_time <= time)
		usleep(1000);
}

void	one_philo(t_philo *philo)
{
	philo->start_time = get_time();
	print_uptate("took a fork", philo);
	philo->running = false;
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	print_uptate("is eating", philo);
	my_sleep(philo->time_to_eat);
	put_forks(philo);
	pthread_mutex_lock(philo->prog->switch_flag);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(philo->prog->switch_flag);
}

void	*philo_thread_part2(t_philo *philo)
{
	pthread_mutex_lock(philo->prog->switch_flag);
	philo->running = true;
	pthread_mutex_unlock(philo->prog->switch_flag);
	if (philo->id % 2 != 0)
		my_sleep(15);
	pthread_mutex_lock(philo->prog->switch_flag);
	while (philo->prog->end == false)
	{
		pthread_mutex_unlock(philo->prog->switch_flag);
		eating(philo);
		print_uptate("is sleeping", philo);
		my_sleep(philo->time_to_sleep);
		print_uptate("is thinking", philo);
		pthread_mutex_lock(philo->prog->switch_flag);
	}
	pthread_mutex_unlock(philo->prog->switch_flag);
	pthread_mutex_lock(philo->prog->switch_flag);
	philo->running = false;
	pthread_mutex_unlock(philo->prog->switch_flag);
	return (NULL);
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->prog->switch_flag);
		if (philo->prog->start_flag == true)
			break ;
		pthread_mutex_unlock(philo->prog->switch_flag);
	}
	pthread_mutex_unlock(philo->prog->switch_flag);
	if (philo->prog->nb_philos == 1)
		return (one_philo(philo), NULL);
	pthread_mutex_lock(philo->prog->switch_flag);
	philo->start_time = get_time();
	pthread_mutex_unlock(philo->prog->switch_flag);
	philo_thread_part2(philo);
	return (NULL);
}
