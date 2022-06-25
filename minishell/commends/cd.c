/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:37:31 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/25 00:45:55 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_pwd(char *temp, t_cd *cd, int j, char *data)
{
	if (!ft_strcmp(temp, ".."))
	{
		if (!treat_prev(cd))
			return (0);
	}
	else if (!ft_strcmp(temp, "."))
		treat_pnt(cd);
	else
	{
		if (j == 0 && data[0] == '/')
		{
			if (cd->pwd)
				free(cd->pwd);
			cd->pwd = ft_strdup("PWD=");
		}
		cd->pwd = ft_strtrim2(cd->pwd, "/");
		cd->pwd = ft_strjoin(cd->pwd, "/");
		cd->pwd = ft_strjoin(cd->pwd, temp);
	}
	chdir(temp);
	return (1);
}

int	check_perms(char *data)
{
	if (access(data, F_OK))
	{
		print_err(data, 1);
		return (0);
	}
	else if (access(data, X_OK))
	{
		print_err(data, 2);
		return (0);
	}
	return (1);
}

int	treat_path(t_cd *cd, char *data)
{
	char	**t;
	char	*temp;
	int		j;

	j = 0;
	if (!check_perms(data))
		return (0);
	t = ft_split_2(data, '/');
	while (t && t[j])
	{
		temp = ft_strdup(t[j]);
		if (!change_pwd(temp, cd, j, data))
		{
			ft_fre(t);
			free(temp);
			return (0);
		}
		free(temp);
		j++;
	}
	ft_fre(t);
	return (1);
}

int	treat_cd(t_cd *cd, int tokn, char *data)
{
	if (!data)
		return (0);
	if (tokn == END_TOKN || tokn == ST_TOKN)
	{
		if (!treat_home(cd))
			return (0);
	}
	else if (data[0] == '-')
	{
		if (!treat_minus(cd))
			return (0);
	}
	else
	{
		if (!treat_path(cd, data))
			return (0);
	}
	return (1);
}

void	ft_cd(t_list **node, t_cd *cd)
{
	t_list	*head;

	head = *node;
	head = head->next;
	while (1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break ;
	}
	save_oldpwd(cd);
	if (!treat_cd(cd, head->next->tokn, head->next->data))
		return ;
	if (get_path(cd->my_env, "PWD"))
	{
		free(cd->my_env[get_pwd(cd->my_env)]);
		cd->my_env[get_pwd(cd->my_env)] = ft_strdup(cd->pwd);
	}
	if (check_exist("OLDPWD", cd->my_env))
		replace_this(cd, cd->oldpwd);
	else
		export_this(cd, cd->oldpwd);
	g_ds = 0;
	return ;
}
