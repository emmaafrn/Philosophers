/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:28:19 by efarin            #+#    #+#             */
/*   Updated: 2021/08/12 12:28:21 by efarin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

uint64_t	get_time_difference(struct timeval old_time)
{
	struct timeval	current_time;
	uint64_t		time_i;
	uint64_t		time_j;

	gettimeofday(&current_time, NULL);
	time_i = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	time_j = old_time.tv_sec * 1000 + old_time.tv_usec / 1000;
	return (time_i - time_j);
}

void	custom_usleep(uint64_t reach)
{
	struct timeval	waiting;
	uint64_t		time;

	time = 0;
	gettimeofday(&waiting, NULL);
	while (time < reach)
	{
		usleep(20);
		time = get_time_difference(waiting);
	}
}
