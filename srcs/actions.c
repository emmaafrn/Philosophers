/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 12:14:37 by efarin            #+#    #+#             */
/*   Updated: 2021/08/13 12:14:41 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_is_speaking(char *str, t_big_struct *data, int id)
{
	pthread_mutex_lock(&data->mutex_voice);
	printf("%llu %d %s\n", get_time_difference(data->start_time), id + 1, str);
	pthread_mutex_unlock(&data->mutex_voice);
}

void	take_two_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	philo_is_speaking("has taken a fork", philo->data, philo->id);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->data->forks[philo->data->nb_philos - 1]);
	else
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	philo_is_speaking("has taken a fork", philo->data, philo->id);
}

void	give_back_two_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo->data->forks[philo->data->nb_philos
			- 1]);
	else
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	pthread_mutex_lock(&philo->data->last_meal_mutex[philo->id]);
	gettimeofday(&philo->data->last_meals[philo->id], NULL);
	philo->data->meals_counter[philo->id]++;
	pthread_mutex_unlock(&philo->data->last_meal_mutex[philo->id]);
}
