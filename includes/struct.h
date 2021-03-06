/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:47 by lguillau          #+#    #+#             */
/*   Updated: 2022/06/09 18:45:47 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef long long			t_ll;
typedef unsigned long long	t_ull;

typedef struct s_philo
{
	int				place;
	t_ull			last_eat;
	int				time_ate;
	int				eat_finished;
	struct s_global	*v;
	pthread_mutex_t	l_eat;
	pthread_mutex_t	t_eat;
}	t_p;

typedef struct s_global
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_eat;
	int				limited_eat;
	int				died;
	int				all_ate;
	t_p				*p;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	all_eat;
	pthread_mutex_t	print;
	t_ull			start_time;
	t_ull			current_time;
}	t_g;

#endif
