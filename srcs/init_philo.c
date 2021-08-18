/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:32:14 by efarin            #+#    #+#             */
/*   Updated: 2021/08/18 17:32:15 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_philo_data(t_big_struct *data)
{
	data->life = 1;
	data->nb_philos = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->meals_nb = 0;
}

int	malloc_philo_data(t_big_struct *data)
{
	data->forks = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	data->last_meals = malloc(data->nb_philos * sizeof(struct timeval));
	data->last_meal_mutex = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	data->meals_counter = malloc(data->nb_philos * sizeof(int));
	data->meals_counter_mutex = malloc(data->nb_philos
			* sizeof(pthread_mutex_t));
	if (!data->forks || !data->last_meal_mutex || !data->meals_counter
		|| !data->meals_counter_mutex || !data->last_meals)
	{
		printf("Error\n");
		return (1);
	}
	return (0);
}

void	philo_mutex_init(t_big_struct *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->last_meal_mutex[i], NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->meals_counter_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mutex_voice, NULL);
}

void	meals_counter_init(t_big_struct *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->meals_counter_mutex[i]);
		data->meals_counter[i] = 0;
		pthread_mutex_unlock(&data->meals_counter_mutex[i]);
		i++;
	}
}
