/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 10:52:29 by efarin            #+#    #+#             */
/*   Updated: 2021/08/11 10:52:32 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*hello_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->data->life)
	{
		if (philo->id % 2 != 0)
			take_two_forks(philo);
		else
		{
			usleep(60);
			take_two_forks(philo);
		}
		philo_is_speaking("is eating", philo->data, philo->id);
		custom_usleep(philo->data->time_to_eat);
		give_back_two_forks(philo);
		philo_is_speaking("is sleeping", philo->data, philo->id);
		custom_usleep(philo->data->time_to_sleep);
		usleep(10);
		philo_is_speaking("is thinking", philo->data, philo->id);
	}
	return (NULL);
}

int	create_threads(t_philo *philo, t_big_struct *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (malloc_philo_data(data))
		return (1);
	meals_counter_init(data);
	init_last_meals(data);
	philo_mutex_init(data);
	while (i < data->nb_philos && ret == 0)
	{
		philo[i].id = i;
		philo[i].data = data;
		ret = pthread_create(&philo[i].thread, NULL, &hello_philo, &philo[i]);
		i++;
	}
	if (i < data->nb_philos)
	{
		good_bye_philo(philo, i);
		return (1);
	}
	return (0);
}
