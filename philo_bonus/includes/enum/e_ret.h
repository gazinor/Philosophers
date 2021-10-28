/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_ret.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 23:39:15 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/15 17:56:08 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_RET_H
# define E_RET_H

enum	e_ret
{
	SUCCESS,
	AC_ERR,
	FORMAT_ERR,
	EMPTY_ARG_ERR,
	LIMITS_ERR,
	MALLOC_ERR,
	PTHREAD_CREATE_ERR,
	PTHREAD_DETACH_ERR,
	FORK_ERR,
	GET_TIME_OF_DAY_ERR,
	USLEEP_ERR,
	MUTEX_LOCK_ERR,
	MUTEX_UNLOCK_ERR,
	SEM_CLOSE_ERR,
	AUTOMATIC_DEATH,
	NO_PHILO
};

#endif
