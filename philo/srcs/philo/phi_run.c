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
#include "philosophers.h"
#include "type/t_ctx.h"
#include "type/t_philo.h"
#include "type/t_fork.h"
#include "enum/e_ret.h"

int	phi_run(void)
{
	t_uint const	nb_philo = phi_ctx_get()->nb_philo;
	t_philo			*philo;
	t_fork			*fork;
	int				ret;
	t_uint			i;

	philo = malloc(nb_philo * sizeof(t_philo));
	if (!philo)
		return (MALLOC_ERR);
	fork = malloc(nb_philo * sizeof(t_fork));
	if (!fork)
		return (MALLOC_ERR);
	phi_philo_init(philo, fork);
	ret = phi_philo_born(philo);
	i = 0;
	while (ret == SUCCESS && i < nb_philo)
		ret = pthread_join(philo[i++].thread, NULL);
	phi_memdel(&philo);
	phi_memdel(&fork);
	return (SUCCESS);
}
