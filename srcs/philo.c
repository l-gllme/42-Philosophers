/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:26:25 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/16 15:51:02 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg, t_g *v)
{
	(void)arg;
	usleep(100000);
	printf("%llu\n", get_time() - v->start_time);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_g	*v;
	pthread_t	*new;
	int	i;

	i = -1;
	v = malloc(sizeof(t_g));
	if (!v)
	{
		ft_putstr_fd("Error: malloc failled in main\n", 2);
		return (-1);
	}
	if (ac == 6)
		v->limited_eat = 1;
	else
		v->limited_eat = 0;
	v->start_time = get_time();
	if (ft_check_args(ac, av, v) == -1)
	{
		free(v);
		return (-1);
	}
	new = malloc(sizeof(pthread_t) * (v->nbr_philo));
	while (++i < v->nbr_philo)
	{
		usleep(100000);
		pthread_create(&new[i], NULL, routine(NULL, v), NULL);
	}
	i = -1;
	while (++i < v->nbr_philo)
		pthread_join(new[i], NULL);
	ft_free(v);
	return (0);
}
