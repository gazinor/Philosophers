/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:18:32 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/14 18:03:13 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "philosophers.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "type/t_fork.h"
#include "enum/e_ret.h"
#include <unistd.h>
#include <stdio.h>

void	*kill_processes(void *arg)
{
	int				i;
	t_philo			*philo;
	t_ctx *const	ctx = phi_ctx_get();

	philo = arg;
	if (sem_wait(ctx->kill_processes))
		phi_err_msg(MUTEX_UNLOCK_ERR);
	i = 0;
	usleep(100);
	while (i < ctx->nb_philo)
		if (philo[i].pid != -1)
			kill(philo[i++].pid, SIGTERM);
	return (NULL);
}

int	free_process(t_philo *philo)
{
	t_ctx *const	ctx = phi_ctx_get();

	if (philo)
		phi_memdel(&philo);
	if (sem_close(ctx->access) || sem_close(ctx->kill_processes)
		|| sem_close(ctx->voice) || sem_close(ctx->forks)
		|| sem_close(ctx->done_eating_philos)
		|| sem_close(ctx->start_processes)
		|| sem_close(ctx->free_process))
		return (SEM_CLOSE_ERR);
	return (SUCCESS);
}

int	join_and_free_philos(t_philo *philo)
{
	int				i;
	int				status;
	t_ctx *const	ctx = phi_ctx_get();

	i = -1;
	while (++i < ctx->nb_philo)
		waitpid(philo[i].pid, &status, 0);
	return (free_process(philo));
}

int	phi_run(void)
{
	t_uint const	nb_philo = phi_ctx_get()->nb_philo;
	t_philo			*philo;
	int				ret;
	pthread_t		thread;

	philo = malloc(nb_philo * sizeof(t_philo));
	if (!philo)
		return (MALLOC_ERR);
	phi_philo_init(philo, NULL);
	if (pthread_create(&thread, NULL, kill_processes, philo))
		return (PTHREAD_CREATE_ERR);
	if (pthread_detach(thread))
		return (PTHREAD_DETACH_ERR);
	ret = phi_philo_born(philo);
	if (ret != SUCCESS)
		if (sem_post(phi_ctx_get()->free_process))
			ret = MUTEX_UNLOCK_ERR;
	ret = join_and_free_philos(philo);
	return (ret);
}
