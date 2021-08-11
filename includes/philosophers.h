/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 10:52:13 by efarin            #+#    #+#             */
/*   Updated: 2021/08/11 10:52:16 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_big_struct
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_nb;
	pthread_mutex_t	*mutex_tab;
}				t_big_struct;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	t_big_struct	*data;
}				t_philo;

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);

#endif