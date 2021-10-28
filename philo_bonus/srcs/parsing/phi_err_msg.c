/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_err_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:56:24 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/12 13:13:22 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "colors.h"
#include "type/t_ctx.h"
#include "err_msg_lookup.h"

int	phi_err_msg(int const err)
{
	int				i;
	int				er;
	t_ctx *const	ctx = phi_ctx_get();

	er = (int)err;
	if (sem_wait(ctx->voice))
		er = MUTEX_LOCK_ERR;
	printf(RED "Error:\n");
	i = 0;
	while (g_err_msg[i].msg && er != g_err_msg[i].err)
		++i;
	printf("%s\n" WHITE, g_err_msg[i].msg);
	return (er);
}
