/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatthes <rmatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:49:31 by rmatthes          #+#    #+#             */
/*   Updated: 2025/07/30 13:17:01 by rmatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Gibt einen String zeichenweise auf den angegebenen Descriptor aus.
void	ft_putstr_fd(char *s, int fd)
{
	// Jedes Zeichen einzeln schreiben, bis das Ende des Strings erreicht ist.
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

// Gibt einen String gefolgt von einem Zeilenumbruch aus.
void	ft_putendl_fd(char *s, int fd)
{
	// String ausgeben und danach den Zeilenumbruch schreiben.
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

// Gibt eine positive Zahl als dezimalen Text auf Standardausgabe aus.
void	ft_putnbr_fd(size_t n)
{
	char	tmp;

	// Höhere Stellen rekursiv ausgeben und danach die letzte Stelle schreiben.
	if (n >= 10)
		ft_putnbr_fd(n / 10);
	tmp = n % 10 + '0';
	write(1, &tmp, 1);
}

// Liefert die aktuelle Zeit in Millisekunden seit einem undefinierten Ursprung.
size_t	get_time(void)
{
	struct timeval	tv;
	size_t			ms;

	// Systemzeit lesen und Sekunden sowie Mikrosekunden in Millisekunden wandeln.
	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

// Wandelt einen nur aus Ziffern bestehenden String in eine Zahl um.
size_t	atosize_t(char *s)
{
	size_t	i;
	size_t	nb;

	// Leere Strings oder Strings ohne Inhalt als null behandeln.
	if (s == NULL || *s == '\0')
		return (0);

	// Ungültige Zeichen vor der eigentlichen Zahlenkonvertierung prüfen.
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}

	// Die Ziffern von links nach rechts zur Dezimalzahl zusammensetzen.
	i = 0;
	nb = 0;
	while (s[i])
	{
		nb = nb + s[i] - '0';
		if (s[i + 1] != '\0')
			nb = nb * 10;
		i++;
	}
	return (nb);
}
