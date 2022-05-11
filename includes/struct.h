/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:47 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/11 16:58:09 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef long long	t_ll;
typedef unsigned long long t_ull;

typedef struct	s_global
{
	int	*args;
	int	len_args;
	t_ull	start_time;
	t_ull	current_time;
}	t_g;

#endif
