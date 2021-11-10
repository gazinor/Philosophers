/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_philo_eat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:39:51 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/21 08:09:02 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "enum/e_state.h"
#include "enum/e_ret.h"
#include <stdio.h>
#include "colors.h"

static int	lock_forks(t_philo *philo, t_fork *fork0, t_fork *fork1)
{
	t_ctx *const	ctx = philo->ctx;
	int				ret;

	if (sem_wait(fork0))
		return (MUTEX_LOCK_ERR);
	if (sem_wait(ctx->access))
		return (MUTEX_LOCK_ERR);
	philo->state = TOOK_FORK;
	if (sem_post(ctx->access))
		return (MUTEX_UNLOCK_ERR);
	ret = phi_philo_state_msg(philo, 0);
	if (ret != SUCCESS)
		return (ret);
	if (sem_wait(fork1))
		return (MUTEX_LOCK_ERR);
	return (phi_philo_state_msg(philo, 0));
}

static int	unlock_forks(t_fork *fork0, t_fork *fork1)
{
	if (sem_post(fork0))
		return (MUTEX_UNLOCK_ERR);
	if (sem_post(fork1))
		return (MUTEX_UNLOCK_ERR);
	return (SUCCESS);
}

static int	update_meal_counts(t_philo *philo)
{
	t_ctx *const	ctx = philo->ctx;

	if (philo->meal_count < ctx->required_meals)
	{
		if (philo->meal_count == ctx->required_meals - 1)
			if (sem_post(ctx->done_eating_philos))
				return (MUTEX_UNLOCK_ERR);
		++philo->meal_count;
		++ctx->meal_count;
	}
	return (SUCCESS);
}

int	phi_philo_eat(t_philo *philo)
{
	t_ctx *const	ctx = philo->ctx;
	int				ret;

	ret = lock_forks(philo, ctx->forks, ctx->forks);
	if (ret == SUCCESS && phi_now() - philo->last_meal >= ctx->time_to_die)
		ret = phi_is_dead(philo);
	if (ret == SUCCESS)
	{
		philo->state = EATING;
		philo->last_meal = phi_now();
		if (philo->last_meal == -1)
			ret = GET_TIME_OF_DAY_ERR;
		else
			ret = phi_philo_state_msg(philo, 0);
	}
	if (ret == SUCCESS)
		ret = update_meal_counts(philo);
	if (ret == SUCCESS)
		ret = phi_philo_wait(philo, ctx->time_to_eat);
	if (ret == SUCCESS)
		ret = unlock_forks(ctx->forks, ctx->forks);
	return (ret);
}
