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

#include <stddef.h>
#include <unistd.h>
#include "philosophers.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "enum/e_ret.h"

int	phi_routine_loop(t_philo *philo, int ret)
{
	t_ctx *const	ctx = philo->ctx;

	while (ret == SUCCESS
		&& (ctx->required_meals == -1
			|| (ctx->meal_count / ctx->nb_philo) < ctx->required_meals))
	{
		if (pthread_mutex_unlock(&ctx->access))
			ret = MUTEX_UNLOCK_ERR;
		if (ret == SUCCESS)
			ret = phi_philo_eat(philo);
		if (ret == SUCCESS)
			ret = phi_philo_sleep(philo);
		if (ret == SUCCESS)
			ret = phi_philo_think(philo);
		if (pthread_mutex_lock(&ctx->access))
			ret = MUTEX_LOCK_ERR;
		if (ret == SUCCESS && ctx->required_meals != -1
			&& philo->meal_count >= ctx->required_meals)
			break ;
	}
	return (ret);
}

void	*phi_routine(void *param)
{
	t_philo *const	philo = (t_philo *)param;
	t_ctx *const	ctx = philo->ctx;
	int				ret;

	ret = SUCCESS;
	if (pthread_mutex_lock(&ctx->start_mutex))
		ret = MUTEX_LOCK_ERR;
	if (pthread_mutex_lock(&ctx->meal_time))
		ret = MUTEX_LOCK_ERR;
	philo->last_meal = phi_now();
	if (philo->last_meal == -1)
		ret = GET_TIME_OF_DAY_ERR;
	if (pthread_mutex_unlock(&ctx->meal_time))
		ret = MUTEX_UNLOCK_ERR;
	if (pthread_mutex_unlock(&ctx->start_mutex))
		ret = MUTEX_UNLOCK_ERR;
	if (pthread_mutex_lock(&ctx->access))
		ret = MUTEX_LOCK_ERR;
	ret = phi_routine_loop(philo, ret);
	if (pthread_mutex_unlock(&ctx->access))
		ret = MUTEX_UNLOCK_ERR;
	if (ret != SUCCESS)
		phi_err_msg(ret);
	return (NULL);
}
