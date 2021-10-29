/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_philo_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:43:10 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/25 17:32:28 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "enum/e_ret.h"
#include "enum/e_state.h"

int	phi_philo_think(t_philo *philo)
{
	int	ret;

	if (pthread_mutex_lock(&philo->ctx->access))
		return (MUTEX_LOCK_ERR);
	philo->state = THINKING;
	if (pthread_mutex_unlock(&philo->ctx->access))
		return (MUTEX_UNLOCK_ERR);
	ret = phi_philo_state_msg(philo);
	return (ret);
}
