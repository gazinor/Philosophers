/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_philo_born.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:44:46 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/21 03:17:32 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philosophers.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "enum/e_ret.h"

int	phi_philo_born(t_philo *philo)
{
	t_ctx *const	ctx = philo->ctx;
	t_lint const	nb_philo = ctx->nb_philo;
	t_lint			i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, phi_routine, philo + i))
			return (PTHREAD_CREATE_ERR);
		++i;
	}
	return (SUCCESS);
}
