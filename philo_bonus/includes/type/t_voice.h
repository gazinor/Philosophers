/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_voice.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 20:10:21 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/13 20:14:19 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_VOICE_H
# define T_VOICE_H

# include <semaphore.h>

typedef sem_t	t_voice;

t_voice	*phi_voice_get(void);

#endif
