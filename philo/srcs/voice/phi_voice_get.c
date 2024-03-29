/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_voice_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 20:12:03 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/13 20:13:02 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type/t_voice.h"

t_voice	*phi_voice_get(void)
{
	static t_voice	voice = PTHREAD_MUTEX_INITIALIZER;

	return (&voice);
}
