/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:22:29 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/11 12:59:26 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error arguments: nbr_of_philo time_to_die time_to_", 2);
		ft_putstr_fd("eat time_to_sleep [nbr_of_time_each_philo_must_eat]\n", 2);
		return (-1);
	}
	while (av[++i])
	{
		if (ft_is_number(av[i]) == -1)
		{
			ft_putstr_fd("Error: numerical arguments only\n", 2);
			return (-1);
		}
	}
	return (0);
}
