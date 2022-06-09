/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:23:36 by lguillau          #+#    #+#             */
/*   Updated: 2022/06/09 17:49:12 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_g *v, t_p *p)
{
	print_line(v, p, 2);
	ft_usleep(v->time_to_sleep, v);
}

void	ft_eat(t_g *v, t_p *p)
{
	if (p->place == 1)
	{
		pthread_mutex_lock(&v->forks[p->place - 1]);
		print_line(v, p, 3);
		pthread_mutex_lock(&v->forks[v->nbr_philo - 1]);
		print_line(v, p, 3);
	}
	else
	{
		pthread_mutex_lock(&v->forks[p->place - 2]);
		print_line(v, p, 3);
		pthread_mutex_lock(&v->forks[p->place - 1]);
		print_line(v, p, 3);
	}
	pthread_mutex_lock(&p->l_eat);
	p->last_eat = get_c_time(v);
	pthread_mutex_unlock(&p->l_eat);
	print_line(v, p, 4);
	ft_usleep(v->time_to_eat, v);
	if (p->place == 1)
		pthread_mutex_unlock(&v->forks[v->nbr_philo - 1]);
	else
		pthread_mutex_unlock(&v->forks[p->place - 2]);
	pthread_mutex_unlock(&v->forks[p->place - 1]);
}

void	ft_think(t_g *v, t_p *p)
{	
	print_line(v, p, 5);
}

int	ft_check_death(t_p *p, t_g *v)
{
	if (v->limited_eat != 0)
	{
		pthread_mutex_lock(&p->t_eat);
		if (p->eat_finished)
		{
			pthread_mutex_unlock(&p->t_eat);
			return (1);
		}
		pthread_mutex_unlock(&p->t_eat);
	}
	pthread_mutex_lock(&p->l_eat);
	if ((get_c_time(v) - p->last_eat) >= (t_ull)v->time_to_die)
	{
		pthread_mutex_unlock(&p->l_eat);
		pthread_mutex_lock(&v->mutex);
		v->died = 1;
		pthread_mutex_unlock(&v->mutex);
		print_death(v, p);
		return (0);
	}
	pthread_mutex_unlock(&p->l_eat);
	return (1);
}
