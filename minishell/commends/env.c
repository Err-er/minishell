/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 06:46:31 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/26 21:51:58 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_list **node, t_cd *cd)
{
	t_list		*head;

	head = *node;
	head = head->next;
	while (1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break ;
	}
	if (head->next->tokn == END_TOKN || head->next->tokn == ST_TOKN)
	{
		if (cd->my_env && *cd->my_env)
			ft_print_env(cd->my_env);
		return ;
	}
	if (head->next->next->tokn != END_TOKN
		&& head->next->next->tokn != ST_TOKN && head->next->next->tokn != PIPE)
	{	
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return ;
	}
}

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
	g_ds = 0;
}

void	remove_vars(t_cd *cd)
{
	int	i;

	i = 0;
	while (cd->my_env && cd->my_env[i])
	{
		if (!ft_strchr(cd->my_env[i], '='))
		{
			unset_this(cd, cd->my_env[i]);
			i = 0;
		}
		i++;
	}
}

void	get_shlvl_value(t_cd *cd)
{
	char	*tmp;

	if (get_path(cd->my_env, "SHLVL"))
	{
		tmp = ft_strtrim(get_path(cd->my_env, "SHLVL"), "\"");
		cd->shlvl = ft_atoi(tmp);
		free(tmp);
	}
	else
		cd->shlvl = 0;
	if (cd->shlvl < 0)
		cd->shlvl = 0;
	else
		cd->shlvl += 1;
}

void	increase_shelvl(t_cd *cd)
{
	char	*temp;
	char	*tmp;

	get_shlvl_value(cd);
	tmp = ft_itoa(cd->shlvl);
	if (get_path(cd->my_env, "SHLVL"))
	{
		temp = ft_strdup("SHLVL=");
		temp = ft_strjoin(temp, tmp);
		replace_this(cd, temp);
	}
	else
	{
		temp = ft_strdup("SHLVL=");
		temp = ft_strjoin(temp, tmp);
		export_this(cd, temp);
	}
	free(tmp);
	free(temp);
	remove_vars(cd);
}
