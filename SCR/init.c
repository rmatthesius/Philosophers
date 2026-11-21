/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatthes <rmatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:48:58 by rmatthes          #+#    #+#             */
/*   Updated: 2025/07/30 13:17:11 by rmatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Liest die Laufzeitdaten ein und initialisiert alle Mutex des Programms.
int	init_programm(t_programm *prog, int argc, char **argv)
{
	size_t	i;

	// Argumente für Anzahl, Mahlzeiten und Sterbezeit speichern.
	prog->nb_philos = atosize_t(argv[1]);
	if (argc == 6)
		prog->meals_to_eat = atosize_t(argv[5]);
	prog->time_to_die = atosize_t(argv[2]);

	// Start- und Endzustand sowie die Argumentanzahl setzen.
	prog->start_flag = false;
	prog->end = false;
	prog->argc = argc;

	// Für jeden Philosophen einen Gabel-Mutex und einen Mahlzeiten-Mutex erstellen.
	i = 0;
	while (i < prog->nb_philos)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL) != 0)
			return (free_mutex_forks(prog, i), 1);
		if (pthread_mutex_init(&prog->meal_locks[i], NULL) != 0)
			return (free_mutex_forks(prog, i), 1);
		i++;
	}

	// Gemeinsame Mutexe für Ausgabe und Startsignal initialisieren.
	if (pthread_mutex_init(prog->stfu, NULL) != 0)
		return (free_mutex_forks(prog, i), 0);
	if (pthread_mutex_init(prog->switch_flag, NULL) != 0)
		return (free_mutex_forks(prog, i),
			pthread_mutex_destroy(prog->stfu), 0);
	return (0);
}

// Initialisiert jeden Philosophen mit seinen Zeiten, Statusdaten und Gabeln.
int	init_philos(t_programm *prog, char **argv)
{
	size_t	i;

	// Jeden Philosophen einzeln mit eindeutiger ID und gemeinsamen Daten verknüpfen.
	i = 0;
	while (i < prog->nb_philos)
	{
		// Essens- und Schlafzeiten sowie persönliche Laufzeitdaten setzen.
		prog->philos[i].time_to_eat = atosize_t(argv[3]);
		prog->philos[i].time_to_sleep = atosize_t(argv[4]);
		prog->philos[i].meals_eaten = 0;
		prog->philos[i].id = i + 1;
		prog->philos[i].start_time = 0;
		prog->philos[i].last_meal = 0;
		prog->philos[i].running = false;

		// Programmzustand, Mahlzeiten-Mutex und rechte Gabel verknüpfen.
		prog->philos[i].prog = prog;
		prog->philos[i].meal_lock = &prog->meal_locks[i];
		prog->philos[i].r_fork = &prog->forks[i];

		// Beim letzten Philosophen die erste Gabel als linke Gabel verwenden.
		if (i != prog->nb_philos - 1)
			prog->philos[i].l_fork = &prog->forks[i + 1];
		else
			prog->philos[i].l_fork = &prog->forks[0];
		i++;
	}
	return (0);
}
