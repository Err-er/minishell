/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_varb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:49:04 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/23 23:14:43 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n - 1)
	{
		i++;
	}
	return (str1[i] - str2[i]);
}

char	*get_path(char **str, char *to_find)
{
	int		i;
	int		j;
	int		x;

	i = -1;
	j = 0;
	if (!str || !*str)
		return (NULL);
	while (str[++i])
	{
		j = 0;
		x = 0;
		while (str[i][j] == to_find[x] && str[i][j] != '=')
		{
			if (str[i][j + 1] == '=')
			{
				if (!ft_strncmp(str[i], to_find, ft_strlen(to_find)))
					return (&str[i][j + 2]);
			}
			x++;
			j++;
		}
	}
	return (NULL);
}
