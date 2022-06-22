/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 05:16:59 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/22 05:17:43 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_cpoy_content(char *s, char *f)
{
	int		i;
	char	*t;
	char	*d;

	i = 0;
	d = ft_strtrim(f, "+");
	t = ft_strdup(d);
	free(d);
	while (s[i] != '=')
		i++;
	if (!s[i])
		return (s);
	i++;
	t = ft_strjoin(t, "=\"");
	t = ft_strjoin(t, &s[i]);
	t = ft_strjoin(t, "\"");
	return (t);
}

void	export_this(t_cd *cd, char *s)
{
	char	**new_env;
	char	**t;
	int		i;

	i = 0;
	while (cd->my_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (cd->my_env[i])
	{
		new_env[i] = ft_strdup(cd->my_env[i]);
		i++;
	}
	t = ft_split_2(s, '=');
	if (t[0] && t[1])
		new_env[i] = ft_cpoy_content(s, t[0]);
	else
	{
		if (ft_strchr(s, '=') && t[0])
		{
			new_env[i] = ft_strdup(t[0]);
			new_env[i] = ft_strjoin(new_env[i], "=\"");
			new_env[i] = ft_strjoin(new_env[i], "\"");
		}
		else
			new_env[i] = ft_strdup(s);
	}
	i++;
	new_env[i] = NULL;
	ft_fre(t);
	ft_fre(cd->my_env);
	cd->my_env = new_env;
}

void	replace_this(t_cd *cd, char *s)
{
	int		i;
	char	*temp;
	char	**t;
	char	**t1;

	i = 0;
	t1 = ft_split_2(s, '=');
	while (cd->my_env[i])
	{
		t = ft_split_2(cd->my_env[i], '=');
		if (t[0] && t1[0] && !ft_strcmp(t[0], t1[0]))
		{
			free(cd->my_env[i]);
			if (t1[1])
			{
				temp = ft_cpoy_content(s, t1[0]);
				cd->my_env[i] = temp;
			}
			else
			{
				if (ft_strchr(s, '='))
				{
					cd->my_env[i] = ft_strdup(t[0]);
					cd->my_env[i] = ft_strjoin(cd->my_env[i], "=\"");
					cd->my_env[i] = ft_strjoin(cd->my_env[i], "\"");
				}
			}
			ft_fre(t);
			ft_fre(t1);
			return ;
		}
		ft_fre(t);
		i++;
	}
}