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
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_big_struct
{
	int					nb_philos;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					meals_nb;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex_voice;
	struct timeval		start_time;
	struct timeval		*last_meals;
	pthread_mutex_t		*last_meal_mutex;
	pthread_mutex_t		*meals_counter_mutex;
	int					*meals_counter;
}				t_big_struct;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	t_big_struct	*data;
}				t_philo;

size_t		ft_strlen(const char *s);
int			ft_atoi(const char *nptr);
void		init_philo_data(t_big_struct *data);
void		init_last_meals(t_big_struct *data);
int			is_there_only_digits(int argc, char **argv);
void		philo_is_speaking(char *str, t_big_struct *data, int id);
void		give_back_two_forks(t_philo *philo);
void		take_two_forks(t_philo *philo);
int			get_philo_data(int argc, char **argv, t_big_struct *data);
uint64_t	get_time_difference(struct timeval old_time);
void		custom_usleep(uint64_t reach);

#endif
