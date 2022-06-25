/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 01:14:58 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/24 21:27:18 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_char(char c)
{
	if (((c < 48 && c != 43) || (c >= 58 && c != 61 && c < 65)
			|| (c >= 91 && c <= 94) || c == 96 || c > 122) && c != 124)
		return (0);
	return (1);
}

int	not_valid(char *s)
{
	g_ds = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (0);
}

int	check_plus(char *s)
{
	int		i;
	int		x;
	char	**t;

	x = 0;
	i = 0;
	t = ft_split_2(s, '=');
	while (t[0][i])
	{
		if (t[0][i] == '+')
			x++;
		i++;
	}
	if (x > 1 || (x == 1 && !t[1])
		|| (t[0][ft_strlen(t[0]) - 1] != '+' && x == 1))
	{
		ft_fre(t);
		return (not_valid(s));
	}
	ft_fre(t);
	return (1);
}

int	check_valid(char *s, char **env)
{
	int		i;
	char	**t;

	i = 0;
	if (!ft_strcmp(s, "="))
		return (not_valid(s));
	while (env && env[i])
	{
		if (!ft_strcmp(s, env[i]))
			return (0);
		i++;
	}
	t = ft_split_2(s, '=');
	if (!t)
		return (0);
	i = 0;
	while (t && t[0][i])
	{
		if (!check_char(t[0][i]) || (ft_isdigit(t[0][0])))
			return (not_valid(s));
		i++;
	}
	ft_fre(t);
	return (check_plus(s));
}
