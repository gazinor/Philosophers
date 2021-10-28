/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:05:11 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/21 08:19:42 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DEBUG */
#include <stdio.h>
#include "colors.h"

#include <stddef.h>
#include <unistd.h>
#include "philosophers.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "enum/e_ret.h"

void	*is_dead_routine(void *param)
{
	t_ctx *const	ctx = phi_ctx_get();
	t_philo *const	philo = (t_philo *)param;
	t_lint			now;
	int				ret;

	ret = SUCCESS;
	while (ret == SUCCESS)
	{
		if (ctx->stop_threads != 0)
			return (NULL);
		now = phi_now();
		if (now == -1)
			ret = GET_TIME_OF_DAY_ERR;
		if ((now - philo->last_meal) >= ctx->time_to_die)
			ret = phi_is_dead(philo);
		if (ret == SUCCESS && usleep(100) == -1)
			ret = USLEEP_ERR;
	}
	if (ret != SUCCESS)
	{
		phi_err_msg(ret);
		if (sem_post(ctx->free_process))
			phi_err_msg(MUTEX_UNLOCK_ERR);
	}
	return (NULL);
}

void	*finished_eating_routine(void *param)
{
	t_ctx *const	ctx = phi_ctx_get();
	int				i;
	int				ret;

	(void)param;
	i = -1;
	ret = SUCCESS;
	while (ret == SUCCESS && ++i < ctx->nb_philo)
	{
		if (ctx->stop_threads != 0)
			return (NULL);
		if (sem_wait(ctx->done_eating_philos))
			ret = MUTEX_LOCK_ERR;
	}
	if (ret == SUCCESS && sem_post(ctx->free_process))
		ret = MUTEX_UNLOCK_ERR;
	if (ret != SUCCESS)
	{
		phi_err_msg(ret);
		if (sem_post(ctx->free_process))
			phi_err_msg(MUTEX_UNLOCK_ERR);
	}
	return (NULL);
}

void	*phi_routine(void *param)
{
	t_ctx *const	ctx = phi_ctx_get();
	t_philo *const	philo = (t_philo *)param;
	int				ret;

	ret = SUCCESS;
	while (ret == SUCCESS)
	{
		if (ctx->required_meals == -1
			|| philo->meal_count < ctx->required_meals)
			ret = phi_philo_eat(philo);
		if (ret == SUCCESS)
			ret = phi_philo_sleep(philo);
		if (ret == SUCCESS)
			ret = phi_philo_think(philo);
		if (ctx->stop_threads != 0)
			return (NULL);
		if (ret != SUCCESS)
			break ;
	}
	if (sem_post(ctx->free_process))
		ret = MUTEX_UNLOCK_ERR;
	if (ret != SUCCESS)
		phi_err_msg(ret);
	return (NULL);
}
