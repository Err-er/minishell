/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:06:37 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/22 10:45:07 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	char	*s;

	s = 0;
	if (!s1)
		return (NULL);
	if (s1 != 0 && set != 0)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		s = (char *)malloc(sizeof(char) * (end - start + 1));
		if (!s)
			return (NULL);
		ft_strlcpy(s, &s1[start], end - start + 1);
	}
	return (s);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (-1);
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	ft_strcmp2(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (0);
	if (!str2)
	{
		if (!str1[0])
			return (0);
		return (1);
	}
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

char	*ft_strnstr(char *str, char *to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		j = 0;
		if (str[(i + j) - 1] == '\n' && str[i + j] == to_find[j])
		{
			while (str[i + j] && str[i + j] == to_find[j])
			{
				if ((str[(i + j) + 1] == '\n' || str[(i + j) + 1] == '\0')
					&& (to_find[j + 1] == '\0'))
					return ("yes");
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	ft_strlcpy(char *dest, char *src, int size)
{
	int	x;
	int	i;

	x = 0;
	while (src[x] != '\0')
	{
		x++;
	}
	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (x);
}
