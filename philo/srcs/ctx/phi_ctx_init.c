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
#include "enum/e_ret.h"

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

int	phi_ctx_init(char const **av, t_ctx *ctx)
{
	int				ret;

	ret = phi_ctx_to_init(av[1], &(ctx->nb_philo));
	if (ctx->nb_philo == 0)
		return (NO_PHILO);
	if (ret == SUCCESS)
		ret = phi_ctx_to_init(av[2], &(ctx->time_to_die));
	if (ret == SUCCESS)
		ret = phi_ctx_to_init(av[3], &(ctx->time_to_eat));
	if (ret == SUCCESS)
		ret = phi_ctx_to_init(av[4], &(ctx->time_to_sleep));
	if (ret == SUCCESS)
		ret = phi_ctx_init_required_meals(av[5], ctx);
	ctx->meal_count = 0;
	ctx->start = 0;
	ctx->finished_eating = 0;
	pthread_mutex_init(&ctx->access, NULL);
	pthread_mutex_init(&ctx->meal_time, NULL);
	pthread_mutex_init(&ctx->start_mutex, NULL);
	pthread_mutex_init(&ctx->voice, NULL);
	return (ret);
}
