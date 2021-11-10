/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_ctx_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 21:34:49 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/21 07:57:37 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type/t_ctx.h"
#include "enum/e_ret.h"

int	phi_ctx_initiate(t_ctx *ctx)
{
	ctx->nb_philo = 0;
	ctx->time_to_die = 0;
	ctx->time_to_eat = 0;
	ctx->time_to_sleep = 0;
	ctx->required_meals = -1;
	ctx->meal_count = 0;
	ctx->start = 0;
	ctx->access = ft_sem_init("access", 1);
	ctx->forks = ft_sem_init("forks", 0);
	ctx->done_eating_philos = ft_sem_init("done_eating_philos", 0);
	ctx->free_process = ft_sem_init("free_process", 0);
	ctx->kill_processes = ft_sem_init("kill_processes", 0);
	ctx->start_processes = ft_sem_init("start_processes", 0);
	ctx->data_races = ft_sem_init("data_races", 0);
	ctx->voice = ft_sem_init("voice", 1);
	if (ctx->free_process == SEM_FAILED || ctx->start_processes == SEM_FAILED
		|| ctx->forks == SEM_FAILED || ctx->done_eating_philos == SEM_FAILED
		|| ctx->kill_processes == SEM_FAILED || ctx->access == SEM_FAILED
		|| ctx->data_races == SEM_FAILED || ctx->voice == SEM_FAILED)
		return (SEM_OPEN_ERR);
	return (SUCCESS);
}
