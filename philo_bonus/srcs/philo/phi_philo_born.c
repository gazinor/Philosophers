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

#include <sys/types.h>
#include <unistd.h>
#include "philosophers.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "enum/e_ret.h"
#include <stdlib.h>
#include <stdio.h>
#include "colors.h"

void	wait_till_the_end(t_philo *philo)
{
	t_ctx *const	ctx = phi_ctx_get();

	while (1)
	{
		if (sem_wait(ctx->free_process))
			phi_err_msg(MUTEX_LOCK_ERR);
		if (sem_post(ctx->free_process))
			phi_err_msg(MUTEX_UNLOCK_ERR);
		++ctx->stop_threads;
		if (sem_post(ctx->kill_processes))
			phi_err_msg(MUTEX_UNLOCK_ERR);
		if (sem_post(ctx->done_eating_philos))
			phi_err_msg(MUTEX_UNLOCK_ERR);
		usleep(5000);
		free_process(philo);
		exit(0);
	}
}

int	launch_process(t_philo *philo, int i)
{
	t_ctx *const	ctx = phi_ctx_get();

	if (!ctx->time_to_eat)
		ctx->time_to_eat = 1;
	if (sem_wait(ctx->start_processes))
		return (MUTEX_LOCK_ERR);
	if (sem_post(ctx->start_processes))
		return (MUTEX_UNLOCK_ERR);
	ctx->start = phi_now();
	philo[i].last_meal = phi_now();
	if (philo[i].idx % 2 == 0)
		phi_philo_wait(philo, ctx->time_to_eat);
	if (philo[i].last_meal == -1)
		return (GET_TIME_OF_DAY_ERR);
	if (pthread_create(&philo[i].wait_thread, NULL,
			is_dead_routine, philo + i))
		return (PTHREAD_CREATE_ERR);
	if (pthread_detach(philo[i].wait_thread))
		return (PTHREAD_DETACH_ERR);
	if (pthread_create(&philo[i].thread, NULL, phi_routine, philo + i))
		return (PTHREAD_CREATE_ERR);
	if (pthread_detach(philo[i].thread))
		return (PTHREAD_DETACH_ERR);
	wait_till_the_end(philo);
	return (SUCCESS);
}

int	phi_fork_philos(t_philo *philo, int i)
{
	if (fork() == 0)
		philo[i].pid = fork();
	else
	{
		free_process(philo);
		exit(0);
	}
	if (philo[i].pid == 0)
	{
		launch_process(philo, i);
	}
	else if (philo[i].pid < 0)
		return (FORK_ERR);
	return (SUCCESS);
}

int	phi_philo_born(t_philo *philo)
{
	t_ctx *const	ctx = phi_ctx_get();
	t_lint const	nb_philo = phi_ctx_get()->nb_philo;
	int				i;
	int				ret;
	pthread_t		thread;

	i = -1;
	ctx->start = phi_now();
	if (ctx->start == -1)
		return (GET_TIME_OF_DAY_ERR);
	while (++i < nb_philo)
	{
		ret = phi_fork_philos(philo, i);
		if (ret != SUCCESS)
			return (ret);
	}
	if (pthread_create(&thread, NULL, finished_eating_routine, philo))
		return (PTHREAD_CREATE_ERR);
	if (pthread_detach(thread))
		return (PTHREAD_DETACH_ERR);
	if (sem_post(ctx->start_processes))
		return (MUTEX_UNLOCK_ERR);
	return (SUCCESS);
}
