/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatthes <rmatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:49:15 by rmatthes          #+#    #+#             */
/*   Updated: 2025/07/30 13:17:18 by rmatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_meals_eaten_msg(t_programm *prog, t_philo *philo)
{
	pthread_mutex_lock(prog->stfu);
	ft_putnbr_fd(philo->id);
	ft_putstr_fd(" has eaten ", 1);
	ft_putnbr_fd(philo->meals_eaten);
	ft_putendl_fd(" times", 1);
	pthread_mutex_unlock(prog->stfu);
}

void	print_uptate(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->prog->stfu);
	pthread_mutex_lock(philo->prog->switch_flag);
	if (philo->prog->end != true)
	{
		ft_putnbr_fd(get_time() - philo->start_time);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->id);
		write(1, " ", 1);
		ft_putendl_fd(str, 1);
	}
	pthread_mutex_unlock(philo->prog->stfu);
	pthread_mutex_unlock(philo->prog->switch_flag);
}

void	print_dead_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->prog->stfu);
	ft_putnbr_fd(get_time() - philo->start_time);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id);
	write(1, " ", 1);
	ft_putendl_fd("died", 1);
	pthread_mutex_unlock(philo->prog->stfu);
	pthread_mutex_unlock(philo->meal_lock);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_uptate("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	print_uptate("has taken a fork", philo);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
