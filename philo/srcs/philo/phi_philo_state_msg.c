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

int	phi_philo_state_msg(t_philo *philo)
{
	t_voice			*voice;
	t_lint			start;
	t_lint const	now = phi_now();
	int				i;

	if (now == -1)
		return (GET_TIME_OF_DAY_ERR);
	if (pthread_mutex_lock(&philo->ctx->access))
		return (MUTEX_LOCK_ERR);
	voice = &philo->ctx->voice;
	start = philo->ctx->start;
	i = 0;
	while (g_state_msg[i].msg && philo->state != g_state_msg[i].state)
		++i;
	if (philo->ctx->required_meals)
	{
		if (pthread_mutex_lock(voice))
			return (MUTEX_LOCK_ERR);
		printf("%6li %4u %s\n", now - start, philo->idx, g_state_msg[i].msg);
		if (pthread_mutex_unlock(voice))
			return (MUTEX_UNLOCK_ERR);
	}
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
