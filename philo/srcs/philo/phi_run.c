/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:18:32 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/14 18:03:13 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "type/t_fork.h"
#include "enum/e_ret.h"

int	check_if_anyone_is_dead(t_philo *philo)
{
	t_ctx *const	ctx = philo->ctx;
	t_lint			now;
	t_uint			i;
	t_lint			since_last_meal;


	philo->ctx->start = phi_now();
	if (philo->ctx->start == -1)
		return (GET_TIME_OF_DAY_ERR);
	if (pthread_mutex_unlock(&philo->ctx->start_mutex))
		return (MUTEX_LOCK_ERR);
	while (1)
	{
		i = 0;
		while (i < ctx->nb_philo)
		{
			now = phi_now();
			if (now == -1)
				return (GET_TIME_OF_DAY_ERR);
			if (pthread_mutex_lock(&philo->ctx->meal_time))
				return (MUTEX_LOCK_ERR);
			if (ctx->finished_eating == ctx->nb_philo)
			{
				if (pthread_mutex_unlock(&philo->ctx->meal_time))
					return (MUTEX_UNLOCK_ERR);
				return (SUCCESS);
			}
			since_last_meal = now - philo[i].last_meal;
			if (pthread_mutex_unlock(&philo->ctx->meal_time))
				return (MUTEX_UNLOCK_ERR);
			if (since_last_meal >= philo->ctx->time_to_die)
				return (is_dead(philo + i));
			++i;
			usleep(10);
		}
	}
}

int	phi_run(t_ctx *ctx)
{
	t_uint const	nb_philo = ctx->nb_philo;
	t_philo			*philo;
	t_fork			*fork;
	int				ret;
	t_uint			i;

	philo = malloc(nb_philo * sizeof(t_philo));
	if (!philo)
		return (MALLOC_ERR);
	fork = malloc(nb_philo * sizeof(t_fork));
	if (!fork)
		return (MALLOC_ERR);
	if (pthread_mutex_lock(&ctx->start_mutex))
		ret = MUTEX_LOCK_ERR;
	phi_philo_init(philo, fork, ctx);
	ret = phi_philo_born(philo);
	if (ret == SUCCESS)
		ret = check_if_anyone_is_dead(philo);
	i = 0;
	while (ret == SUCCESS && i < nb_philo)
		ret = pthread_join(philo[i++].thread, NULL);
	phi_memdel(&philo);
	phi_memdel(&fork);
	return (ret);
}
