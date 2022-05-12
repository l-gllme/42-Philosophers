/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:26:25 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/12 15:01:29 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	(void)arg;
	int i = 0;
	while (++i < 10)
		printf("toto\n");
	return (NULL);
}

void	tata(void *arg)
{
	(void)arg;
	int i = 0;
	while (++i < 10)
		printf("tata\n");
}

int	main(int ac, char **av)
{
	t_g	*v;
	pthread_t	new;

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
	pthread_create(&new, NULL, &routine, NULL);
	tata(NULL);
	ft_free(v);
	return (0);
}
