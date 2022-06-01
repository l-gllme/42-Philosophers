/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:26:25 by lguillau          #+#    #+#             */
/*   Updated: 2022/06/01 15:59:58 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death(t_p *p, t_g *v)
{
	if ((t_ull)(get_time() - v->start_time - p->last_eat) >= (t_ull)v->time_to_die)
	{
		pthread_mutex_lock(&v->mutex);
		print_line(v, p, 1);
		v->died = 1;
		pthread_mutex_unlock(&v->mutex);
		return (0);
	}
	return (1);
}

void	ft_sleep(t_g *v, t_p *p)
{
	t_ull	start_sleep;

	start_sleep = get_c_time(v);

	if (p->place == 1)
		pthread_mutex_unlock(&v->forks[v->nbr_philo - 1]);
	else 
		pthread_mutex_unlock(&v->forks[p->place - 2]);
	pthread_mutex_unlock(&v->forks[p->place - 1]);
	print_line(v, p, 2);
	usleep(v->time_to_sleep * 1000);
}
void	ft_eat(t_g *v, t_p *p)
{
	t_ull	start_eat;

	if (p->place == 1)
		pthread_mutex_lock(&v->forks[v->nbr_philo - 1]);
	else 
		pthread_mutex_lock(&v->forks[p->place - 2]);
	print_line(v, p, 3);
	pthread_mutex_lock(&v->forks[p->place - 1]);
	print_line(v, p, 3);
	start_eat = get_c_time(v);
	usleep(v->time_to_eat * 1000);
	print_line(v, p, 4);
}

void	ft_think(t_g *v, t_p *p)
{	
	print_line(v, p, 5);
}

void	*routine(void *arg)
{
	t_g	*v;
	t_p	*p;
	p = (t_p *)arg;
	v = p->v;
	if (p->place % 2 == 0)
		usleep(v->time_to_eat * 1000);
	while (!v->died)
	{
		ft_eat(v, p);
		ft_sleep(v, p);
		ft_think(v, p);
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
	new = malloc(sizeof(pthread_t) * (v->nbr_philo));
	p = malloc(sizeof(t_p) * (v->nbr_philo));
	v->p = p;
	i = -1;
	while (++i < v->nbr_philo)
	{
		p[i].v = v;
		p[i].place = i + 1;
		p[i].last_eat = 0;
		pthread_create(&new[i], NULL, &routine, &p[i]);
	}
	i = -1;
	while (++i < v->nbr_philo)
		pthread_join(new[i], NULL);
	ft_free(v);
	return (0);
}
