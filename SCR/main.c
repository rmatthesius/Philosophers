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

// Prüft Argumentanzahl und gültige Zahlenbereiche der Eingabe.
int	check_args(int argc, char **argv)
{
	// Die fünf oder sechs erwarteten Argumente validieren.
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

// Zerstört alle bereits erstellten Gabel- und Mahlzeiten-Mutexe.
void	free_mutex_forks(t_programm *prog, int i)
{
	int	j;

	// Nur die Mutexe bis zum angegebenen Index freigeben.
	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&prog->forks[j]);
		pthread_mutex_destroy(&prog->meal_locks[j]);
		j++;
	}
}

// Erstellt alle Philosophen- und Monitor-Threads und wartet auf deren Ende.
int	run(t_programm *prog)
{
	size_t	i;

	// Alle Philosophenthreads nacheinander starten.
	i = 0;
	while (i < prog->nb_philos)
	{
		if (pthread_create(&prog->philos[i].thread, NULL,
				philo_thread, (void *)&prog->philos[i]) != 0)
			return (i);
		i++;
	}
	// Monitorthread starten und anschließend alle Threads zusammenführen.
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

// Markiert den Programmazustand als beendet.
void	end_programm(t_programm *prog)
{
	prog->start_flag = true;
	prog->end = true;
}

// Validiert Eingaben, initialisiert das Programm und startet die Simulation.
int	main(int argc, char **argv)
{
	t_programm	prog;

	// Eingaben prüfen und anschließend Programm sowie Philosophen initialisieren.
	if (check_args(argc, argv) != 0)
		return (ft_putendl_fd("Wrong ARGS", 1), 1);
	if (init_programm(&prog, argc, argv) != 0)
		return (1);
	init_philos(&prog, argv);

	// Simulation starten und bei einem Fehler das Ende setzen.
	if (run(&prog) != 0)
		end_programm(&prog);

	// Alle noch vorhandenen Mutexe vor dem Programmende zerstören.
	free_mutex_forks(&prog, prog.nb_philos);
	pthread_mutex_destroy(prog.stfu);
	pthread_mutex_destroy(prog.switch_flag);
	return (0);
}
