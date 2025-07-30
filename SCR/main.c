/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatthes <rmatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:48:40 by rmatthes          #+#    #+#             */
/*   Updated: 2025/07/30 13:17:14 by rmatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (atosize_t(argv[1]) == 0 || atosize_t(argv[1]) > PHIL_MAX)
		return (ft_putendl_fd("to many philos", 1), 1);
	else if (atosize_t(argv[2]) == 0)
		return (1);
	else if (atosize_t(argv[3]) == 0)
		return (1);
	else if (atosize_t(argv[4]) == 0)
		return (1);
	else if (argc == 6)
		if (atosize_t(argv[5]) == 0)
			return (1);
	return (0);
}

void	free_mutex_forks(t_programm *prog, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&prog->forks[j]);
		pthread_mutex_destroy(&prog->meal_locks[j]);
		j++;
	}
}

int	run(t_programm *prog)
{
	size_t	i;

	i = 0;
	while (i < prog->nb_philos)
	{
		if (pthread_create(&prog->philos[i].thread, NULL,
				philo_thread, (void *)&prog->philos[i]) != 0)
			return (i);
		i++;
	}
	if (pthread_create(&prog->monitor, NULL, monitor_thread, (void *)prog) != 0)
		return (i);
	i = 0;
	while (i < prog->nb_philos)
	{
		if (i == 0)
			pthread_join(prog->monitor, NULL);
		pthread_join(prog->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

void	end_programm(t_programm *prog)
{
	prog->start_flag = true;
	prog->end = true;
}

int	main(int argc, char **argv)
{
	t_programm	prog;

	if (check_args(argc, argv) != 0)
		return (ft_putendl_fd("Wrong ARGS", 1), 1);
	if (init_programm(&prog, argc, argv) != 0)
		return (1);
	init_philos(&prog, argv);
	if (run(&prog) != 0)
		end_programm(&prog);
	free_mutex_forks(&prog, prog.nb_philos);
	pthread_mutex_destroy(prog.stfu);
	pthread_mutex_destroy(prog.switch_flag);
	return (0);
}
