/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <lguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:05:02 by lguillau          #+#    #+#             */
/*   Updated: 2022/06/13 19:57:44 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	cut_death_routine(t_g *v)
{
	if (v->limited_eat != 0)
	{
		pthread_mutex_lock(&v->all_eat);
		if (v->all_ate == v->nbr_philo)
		{
			pthread_mutex_unlock(&v->all_eat);
			return (-1);
		}
		pthread_mutex_unlock(&v->all_eat);
	}
	return (0);
}

void	*death_routine(void *arg)
{
	t_g	*v;
	t_p	*p;
	int	i;

	p = (t_p *)arg;
	v = p->v;
	while (1)
	{
		if (cut_death_routine(v) == -1)
			return (NULL);
		i = -1;
		while (++i < v->nbr_philo)
		{
			if (ft_check_death(&p[i], v) == 0)
				return (NULL);
		}
		usleep(200);
	}
	return (NULL);
}

static int	cut_routine(t_g *v, t_p *p)
{
	if (v->limited_eat != 0)
	{
		if (p->time_ate == v->nbr_of_eat)
		{
			pthread_mutex_lock(&p->t_eat);
			p->eat_finished = 1;
			pthread_mutex_unlock(&p->t_eat);
			pthread_mutex_lock(&v->all_eat);
			v->all_ate++;
			pthread_mutex_unlock(&v->all_eat);
			return (-1);
		}
	}
	ft_eat(v, p);
	ft_sleep(v, p);
	ft_think(v, p);
	return (0);
}

void	*routine(void *arg)
{
	t_g	*v;
	t_p	*p;
	int	i;

	p = (t_p *)arg;
	v = p->v;
	pthread_mutex_lock(&v->mutex);
	i = v->died;
	pthread_mutex_unlock(&v->mutex);
	if (p->place % 2 == 0)
		ft_usleep(v->time_to_eat, v);
	while (i == 0)
	{
		if (cut_routine(v, p) == -1)
			return (NULL);
		pthread_mutex_lock(&v->mutex);
		i = v->died;
		pthread_mutex_unlock(&v->mutex);
		if (v->limited_eat != 0)
			p->time_ate++;
		if (v->nbr_philo % 2 != 0)
			usleep(100);
	}
	return (NULL);
}
