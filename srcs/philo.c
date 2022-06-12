/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:26:25 by lguillau          #+#    #+#             */
/*   Updated: 2022/06/12 19:39:30 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_forks_init(t_g *v)
{
	int	i;

	i = -1;
	v->all_ate = 0;
	v->died = 0;
	pthread_mutex_init(&v->mutex, NULL);
	pthread_mutex_init(&v->print, NULL);
	pthread_mutex_init(&v->all_eat, NULL);
	v->forks = malloc(sizeof(pthread_mutex_t) * (v->nbr_philo));
	while (++i < v->nbr_philo)
		pthread_mutex_init(&v->forks[i], NULL);
}

int	one_philo(t_g *v)
{
	printf("\033[36m0\033[0m \033[33m1\033[0m has taken a fork\n");
	usleep(v->time_to_die * 1000);
	printf("\033[36m%d\033[0m \033[33m1\033[0m died\n", v->time_to_die);
	free(v);
	return (0);
}

void	launch_threads(t_g *v, t_p *p, int i)
{
	pthread_t	*new;
	pthread_t	death_t;

	new = malloc(sizeof(pthread_t) * (v->nbr_philo));
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
	free(new);
}

static int	cut_main(t_g *v, int ac, char **av)
{
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
	return (0);
}

int	main(int ac, char **av)
{
	t_g	*v;
	t_p	*p;

	v = malloc(sizeof(t_g));
	if (cut_main(v, ac, av) == -1)
		return (-1);
	if (v->nbr_philo == 1)
		return (one_philo(v));
	mutex_forks_init(v);
	p = malloc(sizeof(t_p) * (v->nbr_philo));
	v->p = p;
	launch_threads(v, p, -1);
	ft_free(v, p);
	return (0);
}
