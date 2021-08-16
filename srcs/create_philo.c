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

void*	start(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (1)
	{
		if (philo->id % 2 != 0)
			take_two_forks(philo);
		else
		{
			usleep(50);
			take_two_forks(philo);
		}
		philo_is_speaking("is eating", philo->data, philo->id);
		custom_usleep(philo->data->time_to_eat);
		give_back_two_forks(philo);
		philo_is_speaking("is sleeping", philo->data, philo->id);
		custom_usleep(philo->data->time_to_sleep);
		philo_is_speaking("is thinking", philo->data, philo->id);
	}
	return (NULL);
}

void	create_threads(t_philo *philo, t_big_struct *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	data->forks = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	data->last_meals = malloc(data->nb_philos * sizeof(struct timeval));
	data->last_meal_mutex = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	data->meals_counter = malloc(data->nb_philos * sizeof(int));
	data->meals_counter_mutex = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	if (!data->forks || !data->last_meal_mutex || !data->meals_counter
		|| !data->meals_counter_mutex)
		return ;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->meals_counter_mutex[i]);
		data->meals_counter[i] = 0;
		pthread_mutex_unlock(&data->meals_counter_mutex[i]);
		i++;
	}
	i = 0;
	init_last_meals(data);
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->last_meal_mutex[i], NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->meals_counter_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mutex_voice, NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		philo[i].id = i;
		philo[i].data = data;
		ret = pthread_create(&philo[i].thread, NULL, &start, &philo[i]);
		i++;
	}
}

int	error_management(int argc, char **argv, t_big_struct *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error, argument(s) not valid(s)\n");
		return (0);
	}
	init_philo_data(data);
	if (!get_philo_data(argc, argv, data))
	{
		printf("Error, argument(s) not valid(s)!\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int				i;
	t_big_struct	data;
	t_philo			*philo;
	int				end;
	int				meals;

	i = 0;
	end = 0;
	meals = 0;
	if (!error_management(argc, argv, &data))
		return (0);
	philo = malloc(data.nb_philos * sizeof(t_philo));
	if (philo == NULL)
	{
		printf("Error\n");
		return (0);
	}
	gettimeofday(&data.start_time, NULL);
	create_threads(philo, &data);
	while (end == 0)
	{
		i = 0;
		while (i < data.nb_philos && end == 0)
		{
			pthread_mutex_lock(&data.last_meal_mutex[i]);
			if (get_time_difference(data.last_meals[i]) > data.time_to_die
				&& data.time_to_die >= 0)
			{
				end = 1;
				philo_is_speaking("died", &data, i);
			}
			pthread_mutex_unlock(&data.last_meal_mutex[i]);
			pthread_mutex_lock(&data.meals_counter_mutex[i]);
			if (argv[5] && data.meals_counter[i] == data.meals_nb)
				meals++;
			pthread_mutex_unlock(&data.meals_counter_mutex[i]);
			if (meals == data.nb_philos)
			{
				end = 1;
				philo_is_speaking("has eaten enough", &data, i);
			}
			i++;
		}
	}

}
