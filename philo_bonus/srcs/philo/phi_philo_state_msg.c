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

int	phi_philo_state_msg(t_philo *philo, int bypass)
{
	t_hhuint const	state = philo->state;
	t_voice *const	voice = phi_voice_get();
	t_lint const	start = phi_ctx_get()->start;
	t_lint const	now = phi_now();
	int				i;

	if (now == -1)
		return (GET_TIME_OF_DAY_ERR);
	if (bypass == 0 && sem_wait(voice))
		return (MUTEX_LOCK_ERR);
	i = 0;
	while (g_state_msg[i].msg && state != g_state_msg[i].state)
		++i;
	printf("%6li %u %s\n", now - start, philo->idx, g_state_msg[i].msg);
	if (bypass == 0 && sem_post(voice))
		return (MUTEX_UNLOCK_ERR);
	return (SUCCESS);
}
