/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:15:00 by lguillau          #+#    #+#             */
/*   Updated: 2022/05/31 19:32:29 by lguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# include "struct.h"

/* Parsing */

int		ft_check_args(int ac, char **av, t_g *v);

/* Utils */

int		ft_is_number(char *s);
int		ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	free_char_tab(char **s);

void	ft_free(t_g *v);

void	print_line(t_g *v, t_p *p, int choice);
void	ft_usleep(t_ull	time_to_wait);
t_ull	get_c_time(t_g *v);

t_ull	get_time(void);

#endif
