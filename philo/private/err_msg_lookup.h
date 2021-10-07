/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_lookup.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:59:18 by jodufour          #+#    #+#             */
/*   Updated: 2021/09/15 18:01:10 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_MSG_LOOKUP_H
# define ERR_MSG_LOOKUP_H

# include <stddef.h>
# include "enum/e_ret.h"

typedef struct s_err_msg	t_err_msg;

struct s_err_msg
{
	int const	err;
	char const	*msg;
};

static const t_err_msg		g_err_msg[] = {
	{AC_ERR, "Not the right amount of arguments. Try this way :\
		\n- number_of_philosophers\n- time_to_die\n- time_to_eat\n- time_to_sleep\
			\n- [number_of_times_each_philosopher_must_eat]"},
	{FORMAT_ERR, "Wrong argument(s) format"},
	{LIMITS_ERR, "Input is over LONG_INT_MAX value"},
	{MALLOC_ERR, "malloc() failed"},
	{PTHREAD_CREATE_ERR, "pthread_create() failed"},
	{GET_TIME_OF_DAY_ERR, "gettimeofday() failed"},
	{USLEEP_ERR, "usleep() failed"},
	{MUTEX_LOCK_ERR, "pthread_mutex_lock() failed"},
	{MUTEX_UNLOCK_ERR, "pthread_mutex_unlock() failed"},
	{0, NULL}
};

#endif
