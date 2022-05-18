/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:26:25 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/18 15:46:10 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_g	*v;
	t_p	*p;
	p = (t_p *)arg;
	v = p->v;
	while (1)
	{
		usleep(500000);
		printf("\033[36m%llu\033[0m philo %d did something\n", get_time() - v->start_time, p->place);
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
	mutex_forks_init(v);
	new = malloc(sizeof(pthread_t) * (v->nbr_philo));
	p = malloc(sizeof(t_p) * (v->nbr_philo));
	v->p = p;
	i = -1;
	while (++i < v->nbr_philo)
	{
		usleep(60000);
		p[i].v = v;
		p[i].place = i + 1;
		pthread_create(&new[i], NULL, &routine, &p[i]);
	}
	i = -1;
	while (++i < v->nbr_philo)
		pthread_join(new[i], NULL);
	ft_free(v);
	return (0);
}
