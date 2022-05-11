/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:22:29 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/11 17:02:31 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ll	ft_atoi(const char *str)
{
	int		i;
	t_ll	res;
	t_ll	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	ft_check_args(int ac, char **av, t_g *v)
{
	int	i;
	int	j;
	t_ll	number;

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
	i = 0;
	v->len_args = ac - 1;
	v->args = malloc(sizeof(int) * (ac - 1));
	if (!v->args)
	{
		ft_putstr_fd("Error: malloc failed in check_args\n", 2);
		return (-1);
	}
	j = -1;
	while (av[++i])
	{
		if (ft_strlen(av[i]) > 11)
		{
			ft_putstr_fd("Error: number too big detected\n", 2);
			free(v->args);
			return (-1);
		}
		number = ft_atoi(av[i]);
		if (number > 2147483647)
		{
			ft_putstr_fd("Error: number too big detected\n", 2);
			free(v->args);
			return (-1);
		}
		if (number < 0)
		{
			ft_putstr_fd("Error: negative number detected\n", 2);
			free(v->args);
			return (-1);
		}
		v->args[++j] = number;
	}
	return (0);
}
