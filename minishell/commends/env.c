/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 06:46:31 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/19 14:26:54 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(char **env)
{
	int		i;
	int		j;
	char	**s;
	char	*t;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			s = ft_split_2(env[i], '=');
			if (ft_strchr(env[i], '"'))
			{
				printf("%s", s[0]);
				printf("=");
				t = ft_substr(env[i], ft_strlen(s[0]) + 1, ft_strlen(env[i]));
				printf("%s\n", ft_strtrim(t, "\""));
			}
			else
				printf("%s\n", env[i]);
		}
		i++;
	}
	ds = 0;
}

void	increase_shelvl(t_cd *cd)
{
	char	*temp;

	// if (cd->shlvl < 0)
	// 	cd->shlvl = 0;
	// else
		cd->shlvl += 1;
	if (get_path(cd->my_env, "SHLVL"))
	{
		temp = ft_strdup("SHLVL=");
		temp = ft_strjoin(temp, ft_itoa(cd->shlvl));
		replace_this(cd, temp);
	}
}
