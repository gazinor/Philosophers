/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 10:20:29 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/16 01:55:23 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PHILO_H
# define T_PHILO_H

# include <pthread.h>
# include <signal.h>
# include "type/t_int.h"
# include "type/t_fork.h"
# include "type/t_timeval.h"
# include "type/t_ctx.h"

typedef struct s_philo	t_philo;

struct s_philo
{
	t_ctx		*ctx;
	pthread_t	thread;
	pthread_t	wait_thread;
	t_huint		idx;
	t_hhuint	state;
	t_lint		meal_count;
	t_lint		last_meal;
	pid_t		pid;
};

int		phi_philo_born(t_philo *philo);
int		phi_philo_eat(t_philo *philo);
int		phi_philo_sleep(t_philo *philo);
int		phi_philo_state_msg(t_philo *philo, int bypass);
int		phi_philo_think(t_philo *philo);
int		phi_philo_wait(t_philo *philo, t_lint msec);

void	phi_philo_init(t_philo *philo, t_ctx *ctx);

int		phi_is_dead(t_philo *philo);

int		free_process(t_philo *philo, t_ctx *ctx);

#endif
