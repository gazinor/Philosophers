/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ctx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:35:55 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/21 07:56:17 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CTX_H
# define T_CTX_H

# include <pthread.h>
# include "type/t_int.h"
# include "type/t_fork.h"
# include "type/t_voice.h"

typedef struct s_ctx	t_ctx;

struct s_ctx
{
	t_lint			nb_philo;
	t_lint			time_to_die;
	t_lint			time_to_eat;
	t_lint			time_to_sleep;
	t_lint			required_meals;
	t_lint			meal_count;
	t_lint			start;
	sem_t			*access;
	sem_t			*kill_processes;
	sem_t			*free_process;
	sem_t			*done_eating_philos;
	sem_t			*start_processes;
	sem_t			*data_races;
	t_voice			*voice;
	t_fork			*forks;
	int				stop_threads;
};

int		phi_ctx_init_required_meals(char const *s, t_ctx *ctx);
int		phi_ctx_to_init(char const *s, t_lint *to_init);
int		phi_ctx_init(char const **av, t_ctx *ctx);

void	phi_ctx_print(t_ctx *ctx);

sem_t	*ft_sem_init(const char *name, unsigned int value);

int		phi_ctx_initiate(t_ctx *ctx);

#endif
