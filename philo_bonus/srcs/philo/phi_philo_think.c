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

	philo->state = THINKING;
	ret = phi_philo_state_msg(philo, 0);
	if (ret == SUCCESS)
		ret = phi_philo_wait(philo, 0);
	return (ret);
}
