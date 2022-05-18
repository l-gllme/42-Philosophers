/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:47 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/18 16:00:48 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef long long	t_ll;
typedef unsigned long long t_ull;

typedef struct	s_philo
{
	int	place;
	t_ull	last_eat;
	t_ull	last_sleep;
	struct s_global *v;
}	t_p;

typedef struct	s_global
{
	int	nbr_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_of_eat;
	int	limited_eat;
	t_p	*p;
	pthread_mutex_t	*forks;
	t_ull	start_time;
	t_ull	current_time;
}	t_g;

#endif
