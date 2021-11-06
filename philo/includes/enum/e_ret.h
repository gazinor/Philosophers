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
	NO_PHILO,
	NO_VALUE,
	FORMAT_ERR,
	LIMITS_ERR,
	MALLOC_ERR,
	PTHREAD_CREATE_ERR,
	GET_TIME_OF_DAY_ERR,
	USLEEP_ERR,
	MUTEX_LOCK_ERR,
	MUTEX_UNLOCK_ERR,
	ITS_GOOD_DONT_WORRY
};

#endif
