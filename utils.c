/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 21:37:25 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/08 21:50:49 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strrem(char *str, char *rem)
{
	int		i;
	int		j;
	int		x;
	char	*res;
	bool	removed;

	i = -1;
	x = 0;
	removed = false;
	res = malloc(ft_strlen(str) - ft_strlen(rem) + 1);
	while (str[++i])
	{
		j = 0;
		while (rem[j] && rem[j] == str[i + j] && !removed)
			j++;
		if (!rem[j] && !removed)
		{
			i += j;
			removed = true;
		}
		res[x] = str[i];
		x++;
	}
	return (res);
}

char	*mlc_strrchr(char *str, int c)
{
	int		i;
	char	*res;
	char	*buf;

	i = -1;
	res = malloc(ft_strlen(ft_strrchr(str, c)));
	buf = ft_strrchr(str, c);
	while (buf[++i])
		res[i] = buf[i];
	res[i] = '\0';
	return (res);
}
