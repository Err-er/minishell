/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 05:16:59 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/25 19:55:41 by zait-sli         ###   ########.fr       */
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

char	*copy_empty(char *s, char *t)
{
	char	*ret;

	if (ft_strchr(s, '=') && t)
	{
		ret = ft_strdup(t);
		ret = ft_strjoin(ret, "=\"");
		ret = ft_strjoin(ret, "\"");
	}
	else
		ret = ft_strdup(s);
	return (ret);
}

void	export_this(t_cd *cd, char *s)
{
	char	**new_env;
	char	**t;
	int		i;

	i = 0;
	while (cd->my_env && cd->my_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (cd->my_env && cd->my_env[i])
	{
		new_env[i] = ft_strdup(cd->my_env[i]);
		i++;
	}
	t = ft_split_2(s, '=');
	if (t && t[0] && t[1])
		new_env[i] = ft_cpoy_content(s, t[0]);
	else
		new_env[i] = copy_empty(s, t[0]);
	i++;
	new_env[i] = NULL;
	ft_fre(t);
	if (cd->my_env && *cd->my_env)
		ft_fre(cd->my_env);
	cd->my_env = new_env;
}

char	*c_empty(char *s, char *t, char *res)
{
	char	*ret;

	if (ft_strchr(s, '='))
	{
		ret = ft_strdup(t);
		ret = ft_strjoin(ret, "=\"");
		ret = ft_strjoin(ret, "\"");
	}
	else
		ret = ft_strdup(res);
	return (ret);
}

void	replace_this(t_cd *cd, char *s)
{
	int		i;
	char	**t;
	char	**t1;
	char	*tmp;

	t1 = ft_split_2(s, '=');
	i = -1;
	while (cd->my_env[++i])
	{
		t = ft_split_2(cd->my_env[i], '=');
		if (t && t1 && t[0] && t1[0] && !ft_strcmp(t[0], t1[0]))
		{
			tmp = ft_strdup(cd->my_env[i]);
			free(cd->my_env[i]);
			if (t1[1])
				cd->my_env[i] = ft_cpoy_content(s, t1[0]);
			else
				cd->my_env[i] = c_empty(s, t[0], tmp);
			ft_fre(t);
			free(tmp);
			ft_fre(t1);
			return ;
		}
		ft_fre(t);
	}
}
