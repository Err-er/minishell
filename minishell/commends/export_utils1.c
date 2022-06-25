/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 01:14:56 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/25 00:44:55 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_env(t_cd *cd)
{
	int	i;

	i = 0;
	while (cd->my_env[i])
		i++;
	cd->sorted = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cd->my_env[i])
	{
		cd->sorted[i] = ft_strdup(cd->my_env[i]);
		i++;
	}
	cd->sorted[i] = NULL;
}

void	ft_sort_expo(t_cd *cd)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	ft_dup_env(cd);
	while (cd->sorted[i])
	{
		j = 0;
		while (cd->sorted[j])
		{
			if (ft_strcmp(cd->sorted[i], cd->sorted[j]) <= 0)
			{
				temp = cd->sorted[i];
				cd->sorted[i] = cd->sorted[j];
				cd->sorted[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	ft_check_addition(char *s)
{
	int		i;
	int		x;
	char	**t;

	i = 0;
	x = 0;
	t = ft_split_2(s, '=');
	if (!t)
		return (0);
	while (t[0][i])
	{
		if (t[0][i] == '+')
			x++;
		i++;
	}
	if (x != 1 || (x >= 1 && !t[1]) || t[0][ft_strlen(t[0]) - 1] != '+')
	{
		ft_fre(t);
		return (0);
	}
	ft_fre(t);
	return (1);
}

int	check_exist(char *s, char **env)
{
	int		i;
	char	**t;
	char	**t1;

	i = 0;
	if (!env || !env[0])
		return (0);
	t1 = ft_split_2(s, '=');
	t1[0] = ft_strtrim2(t1[0], "+");
	while (env[i])
	{
		t = ft_split_2(env[i], '=');
		if (t[0] && t1[0] && !ft_strcmp(t[0], t1[0]))
		{
			ft_fre(t);
			ft_fre(t1);
			return (1);
		}
		ft_fre(t);
		i++;
	}
	ft_fre(t1);
	return (0);
}

void	ft_print_export(t_cd *cd)
{
	int	i;

	i = 0;
	g_ds = 0;
	if (cd->my_env && cd->my_env[0])
	{
		ft_sort_expo(cd);
		while (cd->sorted[i])
		{
			printf("declare -x %s\n", cd->sorted[i]);
			i++;
		}
		ft_fre(cd->sorted);
	}
}
