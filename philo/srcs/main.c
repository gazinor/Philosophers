/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 23:37:21 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/15 17:46:35 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "type/t_ctx.h"
#include "enum/e_ret.h"

int	main(int ac, char const **av)
{
	t_ctx	*ctx;
	int		ret;

	ctx = &(t_ctx){0, 0, 0, 0, -1, 0, 0, 0,
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER};
	if (ac == 5 || ac == 6)
	{
		ret = phi_format_check(av);
		if (ret == SUCCESS)
			ret = phi_ctx_init(av, ctx);
		if (ret == SUCCESS)
			ret = phi_run(ctx);
	}
	else
		ret = AC_ERR;
	if (ret != SUCCESS)
		phi_err_msg(ret);
	return (SUCCESS);
}
