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
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "enum/e_state.h"
#include "enum/e_ret.h"

int	is_dead(t_philo *philo)
{
	philo->state = DEAD;
	return (phi_philo_state_msg(philo));
}

int	phi_philo_wait(t_philo *philo, t_lint msec)
{
	t_ctx *const	ctx = phi_ctx_get();
	t_lint			start;
	t_lint			now;
	t_lint			waited;

	start = phi_now();
	if (start == -1)
		return (GET_TIME_OF_DAY_ERR);
	waited = (now = phi_now()) - start;
	if ((now - philo->last_meal) >= ctx->time_to_die)
		return (is_dead(philo));
	while (now != -1 && waited < msec)
	{
		if (usleep(100) == -1)
			return (USLEEP_ERR);
		waited = (now = phi_now()) - start;
		if ((now - philo->last_meal) >= ctx->time_to_die)
			return (is_dead(philo));
	}
	if (now == -1)
		return (GET_TIME_OF_DAY_ERR);
	return (SUCCESS);
}
