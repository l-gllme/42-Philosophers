/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:13:59 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/10 14:27:45 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_number(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
	}
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_char_tab(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (s[i])
			free(s[i]);
		i++;
	}
	free(s);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	nb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = n * -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, &*s, ft_strlen(s));
}
