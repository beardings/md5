/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mponomar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 20:53:02 by mponomar          #+#    #+#             */
/*   Updated: 2016/12/02 19:42:50 by mponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char			*ft_strcat(char *s1, const char *s2)
{
	char		*ss1;
	const char	*ss2;

	ss1 = s1;
	ss2 = s2;
	while (*ss1)
		ss1++;
	while (*ss2)
		*ss1++ = *ss2++;
	*ss1 = '\0';
	return (s1);
}
