/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:29:39 by efarin            #+#    #+#             */
/*   Updated: 2021/08/18 17:29:40 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	args_errors(int argc, char **argv, t_big_struct *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error, argument(s) not valid(s) !\n");
		return (1);
	}
	init_philo_data(data);
	if (!get_philo_data(argc, argv, data))
	{
		printf("Error, argument(s) not valid(s) !\n");
		return (1);
	}
	return (0);
}

void	good_bye_philo(t_philo *philo, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		pthread_detach(philo[i].thread);
		i++;
	}
}

void	end_up_philo(t_big_struct *data, t_philo *philo, int detach)
{
	if (data->forks)
		free(data->forks);
	if (data->last_meals)
		free(data->last_meals);
	if (data->meals_counter)
		free(data->meals_counter);
	if (data->last_meal_mutex)
		free(data->last_meal_mutex);
	if (data->meals_counter_mutex)
		free(data->meals_counter_mutex);
	if (detach == 1)
		good_bye_philo(philo, data->nb_philos);
	if (philo)
		free(philo);
}
