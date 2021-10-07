/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_strcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <glaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 01:37:05 by glaurent          #+#    #+#             */
/*   Updated: 2021/09/11 01:38:52 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	phi_strcmp(char const *s1, char const *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
