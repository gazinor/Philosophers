/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_ctx_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 21:59:44 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/20 16:55:12 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "enum/e_ret.h"
#include "enum/e_state.h"
#include <fcntl.h>
#include <unistd.h>

sem_t	*ft_sem_init(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

int	phi_ctx_init_required_meals(char const *s, t_ctx *ctx)
{
	if (!s)
		return (SUCCESS);
	while (phi_is_space(*s))
		++s;
	if (*s == '+')
		++s;
	while (*s == '0' && phi_is_digit(*(s + 1)))
		++s;
	ctx->required_meals = phi_atol(s);
	return (phi_limits_check(s, ctx->required_meals));
}

int	phi_ctx_to_init(char const *s, t_lint *to_init)
{
	while (phi_is_space(*s))
		++s;
	if (*s == '+')
		++s;
	while (*s == '0' && phi_is_digit(*(s + 1)))
		++s;
	*to_init = phi_atol(s);
	return (phi_limits_check(s, *to_init));
}

int	phi_logical_death(t_ctx *const ctx)
{
	t_philo	philo;

	philo.idx = 1;
	philo.state = DEAD;
	if (ctx->nb_philo <= 0)
		return (NO_PHILO);
	return (SUCCESS);
}

int	phi_ctx_init(char const **av, t_ctx *ctx)
{
	int				ret;

	ret = phi_ctx_to_init(av[1], &(ctx->nb_philo));
	if (ret == SUCCESS)
		ret = phi_ctx_to_init(av[2], &(ctx->time_to_die));
	if (ret == SUCCESS)
		ret = phi_ctx_to_init(av[3], &(ctx->time_to_eat));
	if (ret == SUCCESS)
		ret = phi_ctx_to_init(av[4], &(ctx->time_to_sleep));
	if (ret == SUCCESS)
		ret = phi_ctx_init_required_meals(av[5], ctx);
	if (ret == SUCCESS)
		ret = phi_logical_death(ctx);
	if (ret != SUCCESS)
		return (ret);
	sem_close(ctx->forks);
	sem_unlink("forks");
	ctx->forks = ft_sem_init("forks", ctx->nb_philo);
	sem_close(ctx->kill_processes);
	sem_unlink("kill_processes");
	ctx->kill_processes = ft_sem_init("kill_processes", ctx->nb_philo - 1);
	ctx->stop_threads = 0;
	if (ctx->forks == SEM_FAILED || ctx->kill_processes == SEM_FAILED)
		return (SEM_OPEN_ERR);
	return (ret);
}
