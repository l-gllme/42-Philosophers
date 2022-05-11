/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:51:54 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/11 16:49:27 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ull	get_time(void)
{
	t_ull	time;
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (time);
}
