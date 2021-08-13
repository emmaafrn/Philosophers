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
			usleep(40);
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
	data->mutex_tab = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	data->last_meals = malloc(data->nb_philos * sizeof(unsigned long long));
	if (data->mutex_tab == NULL)
		return ;
	init_last_meals(data);
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->mutex_tab[i], NULL);
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

int	main(int argc, char **argv)
{
	int				i;
	t_big_struct	data;
	t_philo			*philo;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error, argument(s) not valid(s)\n");
		return (0);
	}
	init_philo_data(&data);
	if (!get_philo_data(argc, argv, &data))
	{
		printf("Error, argument(s) not valid(s)!\n");
		return (0);
	}
	philo = malloc(data.nb_philos * sizeof(t_philo));
	if (philo == NULL)
	{
		printf("Error\n");
		return (0);
	}
	gettimeofday(&data.start_time, NULL);
	create_threads(philo, &data);
	while (i < data.nb_philos)
	{
		if (data.last_meals[i] > data.time_to_die && data.time_to_die >= 0)
			break ;
		i++;
	}

}
