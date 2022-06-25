/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 01:15:01 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/25 01:16:27 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_add_content(char *old, char *new, char *n)
{
	int		i;
	char	*t;
	char	*d;

	i = 0;
	t = ft_strdup(n);
	while (old[i] != '=')
		i++;
	i++;
	d = ft_strtrim(old, "\"=");
	t = ft_strjoin(t, "=\"");
	t = ft_strjoin(t, &d[i]);
	t = ft_strjoin(t, &new[i + 1]);
	t = ft_strjoin(t, "\"");
	free(d);
	return (t);
}

char	*ft_add_nocontent(char *old, char *n)
{
	char	*temp;

	temp = ft_strdup(old);
	temp = ft_strjoin(temp, "=\"");
	temp = ft_strjoin(temp, &n[1]);
	temp = ft_strjoin(temp, "\"");
	return (temp);
}

void	add_this(t_cd *cd, char *s)
{
	int		i;
	char	*temp;
	char	**t;
	char	**t1;

	i = 0;
	t1 = ft_split_2(s, '+');
	while (cd->my_env[i])
	{
		t = ft_split_2(cd->my_env[i], '=');
		if (t[0] && t1[0] && !ft_strcmp(t[0], t1[0]))
		{
			if (t[1])
				temp = ft_add_content(cd->my_env[i], s, t1[0]);
			else
				temp = ft_add_nocontent(cd->my_env[i], t1[1]);
			free(cd->my_env[i]);
			cd->my_env[i] = temp;
			ft_fre(t);
			ft_fre(t1);
			return ;
		}
		ft_fre(t);
		i++;
	}
}
