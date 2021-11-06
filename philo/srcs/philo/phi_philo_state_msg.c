/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_philo_state_msg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 11:53:51 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/20 22:28:07 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "philosophers.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "type/t_voice.h"
#include "state_msg_lookup.h"
#include "enum/e_ret.h"

int	lock_sem_and_print_msg(t_lint time, t_philo *philo, int i)
{
	t_voice			*voice;

	voice = &philo->ctx->voice;
	if (philo->ctx->required_meals)
	{
		if (pthread_mutex_lock(voice))
			return (MUTEX_LOCK_ERR);
		printf("%6li %4u %s\n", time, philo->idx, g_state_msg[i].msg);
		if (pthread_mutex_unlock(voice))
			return (MUTEX_UNLOCK_ERR);
	}
	return (SUCCESS);
}

int	phi_philo_state_msg(t_philo *philo)
{
	t_lint			start;
	t_lint const	now = phi_now();
	int				i;

	if (now == -1)
		return (GET_TIME_OF_DAY_ERR);
	if (pthread_mutex_lock(&philo->ctx->access))
		return (MUTEX_LOCK_ERR);
	start = philo->ctx->start;
	i = 0;
	while (g_state_msg[i].msg && philo->state != g_state_msg[i].state)
		++i;
	i = lock_sem_and_print_msg(now - start, philo, i);
	if (i != SUCCESS)
		return (i);
	if (pthread_mutex_unlock(&philo->ctx->access))
		return (MUTEX_UNLOCK_ERR);
	if (pthread_mutex_lock(&philo->ctx->access))
		return (MUTEX_LOCK_ERR);
	if (philo->state == DEAD)
		philo->ctx->required_meals = 0;
	if (pthread_mutex_unlock(&philo->ctx->access))
		return (MUTEX_UNLOCK_ERR);
	return (SUCCESS);
}
