/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_philo_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:55:43 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/20 16:26:26 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"
#include "colors.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "enum/e_state.h"
#include "enum/e_ret.h"
#include <stdio.h>
#include <fcntl.h>

int	phi_is_dead(t_philo *philo)
{
	t_ctx *const	ctx = philo->ctx;

	if (sem_wait(ctx->voice))
		return (MUTEX_LOCK_ERR);
	philo->state = DEAD;
	phi_philo_state_msg(philo, 1);
	if (sem_post(ctx->free_process))
		return (MUTEX_UNLOCK_ERR);
	return (SUCCESS);
}

int	phi_philo_wait(t_philo *philo, t_lint msec)
{
	t_lint			start;
	t_lint			now;
	t_lint			waited;

	(void)philo;
	start = phi_now();
	if (start == -1)
		return (GET_TIME_OF_DAY_ERR);
	waited = (now = phi_now()) - start;
	while (now != -1 && waited < msec)
	{
		if (usleep(100) == -1)
			return (USLEEP_ERR);
		waited = (now = phi_now()) - start;
	}
	if (now == -1)
		return (GET_TIME_OF_DAY_ERR);
	return (SUCCESS);
}
