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
	t_lint			finished_eating;
	pthread_mutex_t	access;
	pthread_mutex_t	meal_time;
	pthread_mutex_t	start_mutex;
	t_voice			voice;
};

int		phi_ctx_init_nb_philo(char const *s);
int		phi_ctx_init_time_to_die(char const *s);
int		phi_ctx_init_time_to_eat(char const *s);
int		phi_ctx_init_time_to_sleep(char const *s);
int		phi_ctx_init_required_meals(char const *s, t_ctx *ctx);
int		phi_ctx_to_init(char const *s, t_lint *to_init);
int		phi_ctx_init(char const **av, t_ctx *ctx);

void	phi_ctx_print(t_ctx *ctx);

t_ctx	*phi_ctx_get(void);

#endif
