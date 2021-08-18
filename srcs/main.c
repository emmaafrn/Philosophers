/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:45:45 by efarin            #+#    #+#             */
/*   Updated: 2021/08/18 17:45:47 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	meals_number_checker(t_big_struct *data, int philo_nb, int meals_nb)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < philo_nb)
	{
		pthread_mutex_lock(&data->meals_counter_mutex[i]);
		if (data->meals_counter[i] == meals_nb)
			res++;
		pthread_mutex_unlock(&data->meals_counter_mutex[i]);
		i++;
	}
	if (res == philo_nb)
		return (1);
	return (0);
}

void	main_while(t_big_struct *data, char **argv, int end)
{
	int	i;

	while (end == 0)
	{
		i = -1;
		while (++i < data->nb_philos && end == 0)
		{
			pthread_mutex_lock(&data->last_meal_mutex[i]);
			if (get_time_difference(data->last_meals[i]) > data->time_to_die
				&& data->time_to_die >= 0)
			{
				end = 1;
				data->life = 0;
				philo_is_dying("died", data, i);
			}
			pthread_mutex_unlock(&data->last_meal_mutex[i]);
			if (argv[5] && meals_number_checker(data,
					data->nb_philos, data->meals_nb))
			{
				end = 1;
				data->life = 0;
				philo_is_dying("Everyone has eaten enough", data, -1);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_big_struct	data;
	t_philo			*philo;
	int				end;

	end = 0;
	if (args_errors(argc, argv, &data))
		return (0);
	philo = malloc(data.nb_philos * sizeof(t_philo));
	if (philo == NULL)
	{
		printf("Error\n");
		return (0);
	}
	gettimeofday(&data.start_time, NULL);
	if (!create_threads(philo, &data))
		main_while(&data, argv, end);
	else
	{
		end_up_philo(&data, philo, 0);
		return (0);
	}
	end_up_philo(&data, philo, 1);
	return (0);
}
