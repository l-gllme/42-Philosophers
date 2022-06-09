/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:26:25 by lguillau          #+#    #+#             */
/*   Updated: 2022/06/09 13:33:34 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		print_line(v, p, 1);
		pthread_mutex_lock(&v->mutex);
		v->died = 1;
		pthread_mutex_unlock(&v->mutex);
		return (0);
	}
	pthread_mutex_unlock(&p->l_eat);
	return (1);
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
		i = -1;
		if (v->limited_eat != 0)
		{
			pthread_mutex_lock(&v->all_eat);
			if (v->all_ate == v->nbr_philo)
			{
				pthread_mutex_unlock(&v->all_eat);
				return (NULL);
			}
			pthread_mutex_unlock(&v->all_eat);
		}
		while (++i < v->nbr_philo)
		{
			if (ft_check_death(&p[i], v) == 0)
				return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}

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
				return (NULL);
			}
		}
		ft_eat(v, p);
		ft_sleep(v, p);
		ft_think(v, p);
		pthread_mutex_lock(&v->mutex);
		i = v->died;
		pthread_mutex_unlock(&v->mutex);
		if (v->limited_eat != 0)
			p->time_ate++;
	}
	return (NULL);
}

void	mutex_forks_init(t_g *v)
{
	int	i;

	i = -1;
	v->forks = malloc(sizeof(pthread_mutex_t) * (v->nbr_philo));
	while (++i < v->nbr_philo)
		pthread_mutex_init(&v->forks[i], NULL);
}

int	one_philo(t_g *v)
{
	printf("\033[36m0\033[0m \033[33m1\033[0m has taken a fork\n");
	usleep(v->time_to_die * 1000);
	printf("\033[36m%d\033[0m \033[33m1\033[0m died\n", v->time_to_die);
	ft_free(v);
	return (0);
}

int	main(int ac, char **av)
{
	t_g	*v;
	pthread_t	*new;
	pthread_t	death_t;
	t_p	*p;
	int	i;

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
	if (v->nbr_philo == 1)
		return (one_philo(v));
	mutex_forks_init(v);
	v->died = 0;
	pthread_mutex_init(&v->mutex, NULL);
	pthread_mutex_init(&v->print, NULL);
	pthread_mutex_init(&v->all_eat, NULL);
	new = malloc(sizeof(pthread_t) * (v->nbr_philo));
	p = malloc(sizeof(t_p) * (v->nbr_philo));
	v->p = p;
	v->all_ate = 0;
	i = -1;
	while (++i < v->nbr_philo)
	{
		p[i].v = v;
		p[i].place = i + 1;
		p[i].last_eat = 0;
		p[i].time_ate = 0;
		p[i].eat_finished = 0;
		pthread_mutex_init(&p[i].l_eat, NULL);
		pthread_mutex_init(&p[i].t_eat, NULL);
		pthread_create(&new[i], NULL, &routine, &p[i]);
	}
	pthread_create(&death_t, NULL, &death_routine, p);
	i = -1;
	while (++i < v->nbr_philo)
		pthread_join(new[i], NULL);
	pthread_join(death_t, NULL);
	ft_free(v);
	return (0);
}
