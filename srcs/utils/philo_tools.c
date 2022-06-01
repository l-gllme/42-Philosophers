/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <lguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:30:37 by lguillau          #+#    #+#             */
/*   Updated: 2022/06/01 15:34:01 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_line(t_g *v, t_p *p, int choice)
{
	pthread_mutex_lock(&v->print);
	printf("\033[36m%llu\033[0m \033[33m%d\033[0m", get_c_time(v), p->place);
	if (choice == 1)
		printf(" died\n");
	else if (choice == 2)
		printf(" is sleeping\n");
	else if (choice == 3)
		printf(" as taken a fork\n");
	else if (choice == 4)
		printf(" is eating\n");
	else if (choice == 5)
		printf(" is thinking\n");
	pthread_mutex_unlock(&v->print);
}

void	ft_usleep(t_ull	time_to_wait)
{
	t_ull	t;

	t = get_time();
	while ((get_time() - t) < time_to_wait)
		usleep(time_to_wait / 10);
}

t_ull	get_c_time(t_g *v)
{
	return (get_time() - v->start_time);
}
