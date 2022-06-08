/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <lguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:30:37 by lguillau          #+#    #+#             */
/*   Updated: 2022/06/08 18:20:04 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_line(t_g *v, t_p *p, int choice)
{
	t_ull	time;

	time = get_c_time(v);
	pthread_mutex_lock(&v->mutex);
	if (v->died)
	{
		pthread_mutex_unlock(&v->mutex);
		return ;
	}
	pthread_mutex_unlock(&v->mutex);
	pthread_mutex_lock(&v->print);
	printf("\033[36m%llu\033[0m \033[33m%d\033[0m", time, p->place);
	if (choice == 1)
		printf(" died\n");
	else if (choice == 2)
		printf(" is sleeping\n");
	else if (choice == 3)
		printf(" has taken a fork\n");
	else if (choice == 4)
		printf(" is eating\n");
	else if (choice == 5)
		printf(" is thinking\n");
	pthread_mutex_unlock(&v->print);
}

void	ft_usleep(t_ull	time_to_wait, t_g *v)
{
	t_ull	t;

	t = get_time();
	while ((get_time() - t) < time_to_wait)
	{
		pthread_mutex_lock(&v->mutex);
		if (v->died == 1)
		{
			pthread_mutex_unlock(&v->mutex);
			return ;
		}
		pthread_mutex_unlock(&v->mutex);
		usleep(time_to_wait / 10);
	}
}

t_ull	get_c_time(t_g *v)
{
	return (get_time() - v->start_time);
}
