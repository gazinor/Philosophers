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
#include "stdio.h"

static int	lock_forks(t_philo *philo, t_fork *fork0, t_fork *fork1)
{
	int	ret;

	phi_philo_wait(philo, 0);
	if (pthread_mutex_lock(fork0))
		return (MUTEX_LOCK_ERR);
	if (pthread_mutex_lock(&philo->ctx->access))
		return (MUTEX_LOCK_ERR);
	++philo->nb_locked_forks;
	philo->state = TOOK_FORK;
	if (pthread_mutex_unlock(&philo->ctx->access))
		return (MUTEX_UNLOCK_ERR);
	ret = phi_philo_state_msg(philo);
	if (ret != SUCCESS)
		return (ret);
	if (fork0 == fork1)
		return (phi_philo_wait(philo, philo->ctx->time_to_die * 2 + 1));
	phi_philo_wait(philo, 0);
	if (pthread_mutex_lock(fork1))
		return (MUTEX_LOCK_ERR);
	if (pthread_mutex_lock(&philo->ctx->access))
		return (MUTEX_LOCK_ERR);
	++philo->nb_locked_forks;
	if (pthread_mutex_unlock(&philo->ctx->access))
		return (MUTEX_UNLOCK_ERR);
	return (phi_philo_state_msg(philo));
}

static int	unlock_forks(t_philo *philo, t_fork *fork0, t_fork *fork1)
{
	t_fork	*tmp;

	if (pthread_mutex_lock(&philo->ctx->access))
		return (MUTEX_LOCK_ERR);
	if (!(philo->idx % 2))
	{
		tmp = fork0;
		fork0 = fork1;
		fork1 = tmp;
	}
	if (philo->nb_locked_forks >= 1)
	{
		if (pthread_mutex_unlock(fork0))
			return (MUTEX_UNLOCK_ERR);
		if (philo->nb_locked_forks > 1)
			if (pthread_mutex_unlock(fork1))
				return (MUTEX_UNLOCK_ERR);
	}
	if (pthread_mutex_unlock(&philo->ctx->access))
		return (MUTEX_UNLOCK_ERR);
	return (SUCCESS);
}

static int	update_meal_counts(t_philo *philo, t_ctx *const ctx)
{
	if (pthread_mutex_lock(&ctx->access))
		return (MUTEX_LOCK_ERR);
	if (philo->meal_count < ctx->required_meals)
	{
		++philo->meal_count;
		++ctx->meal_count;
	}
	if (philo->meal_count == ctx->required_meals)
	{
		if (pthread_mutex_lock(&ctx->meal_time))
			return (MUTEX_LOCK_ERR);
		++ctx->finished_eating;
		if (pthread_mutex_unlock(&ctx->meal_time))
			return (MUTEX_UNLOCK_ERR);
	}
	if (pthread_mutex_unlock(&ctx->access))
		return (MUTEX_UNLOCK_ERR);
	return (SUCCESS);
}

int	after_eat(t_philo *philo, int ret)
{
	t_ctx *const	ctx = philo->ctx;

	if (ret == SUCCESS)
		ret = phi_philo_state_msg(philo);
	if (ret == SUCCESS)
		ret = update_meal_counts(philo, ctx);
	if (ret == SUCCESS)
		ret = phi_philo_wait(philo, ctx->time_to_eat);
	if (ret == SUCCESS)
		ret = unlock_forks(philo, philo->fork_right, philo->fork_left);
	return (ret);
}

int	phi_philo_eat(t_philo *philo)
{
	t_ctx *const	ctx = philo->ctx;
	int				ret;

	if (philo->idx % 2)
		ret = lock_forks(philo, philo->fork_right, philo->fork_left);
	else
		ret = lock_forks(philo, philo->fork_left, philo->fork_right);
	if (ret != SUCCESS)
		return (ret);
	if (pthread_mutex_lock(&ctx->access))
		return (MUTEX_LOCK_ERR);
	philo->state = EATING;
	if (pthread_mutex_unlock(&ctx->access))
		return (MUTEX_UNLOCK_ERR);
	ret = phi_philo_wait(philo, 0);
	if (pthread_mutex_lock(&ctx->meal_time))
		return (MUTEX_LOCK_ERR);
	philo->last_meal = phi_now();
	if (pthread_mutex_unlock(&ctx->meal_time))
		return (MUTEX_UNLOCK_ERR);
	if (philo->last_meal == -1)
		return (GET_TIME_OF_DAY_ERR);
	return (after_eat(philo, ret));
}
