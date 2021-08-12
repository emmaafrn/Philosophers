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

void	init_philo_data(t_big_struct *data)
{
	data->nb_philos = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->meals_nb = 0;
}

int	is_there_only_digits(int argc, char **argv)
{
	int	i;
	int	j;
	int	str_len;

	i = 1;
	while (i < argc)
	{
		j = 0;
		str_len = ft_strlen(argv[i]);
		while (argv[i][j] && argv[i][j] >= '0' && argv[i][j] <= '9')
			j++;
		if (j < str_len)
			return (0);
		i++;
	}
	return (1);
}

int	get_philo_data(int argc, char **argv, t_big_struct *data)
{
	if (!is_there_only_digits(argc, argv))
		return (0);
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_nb = ft_atoi(argv[5]);
	return (1);
}

void	philo_is_speaking(char *str, t_big_struct *data, int id)
{
	pthread_mutex_lock(&data->mutex_voice);
	printf("%llu %d %s\n", get_time_difference(data->start_time),id + 1, str);
	pthread_mutex_unlock(&data->mutex_voice);
}

void	give_back_two_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mutex_tab[philo->id]);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo->data->mutex_tab[philo->data->nb_philos - 1]);
	else
		pthread_mutex_unlock(&philo->data->mutex_tab[philo->id - 1]);
}

void	take_two_forks(t_philo *philo)
{
	usleep(80);
	pthread_mutex_lock(&philo->data->mutex_tab[philo->id]);
	philo_is_speaking("as taken a fork", philo->data, philo->id);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->data->mutex_tab[philo->data->nb_philos - 1]);
	else
		pthread_mutex_lock(&philo->data->mutex_tab[philo->id - 1]);
	philo_is_speaking("as taken a fork", philo->data, philo->id);
}

void*	start(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (1)
	{
		take_two_forks(philo);
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
	if (data->mutex_tab == NULL)
		return ;
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
	t_big_struct	data;
	t_philo			*philo;

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
	while (1)
	{

	}
}
