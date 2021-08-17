/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 12:14:49 by efarin            #+#    #+#             */
/*   Updated: 2021/08/13 12:14:51 by efarin           ###   ########lyon.fr   */
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
