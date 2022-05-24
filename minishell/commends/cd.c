/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:37:31 by zait-sli          #+#    #+#             */
/*   Updated: 2022/05/24 06:15:04 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_pwd(char **env)
{
	int i = 0;
	
	while(env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4))
			i++;
		else
			return(i);
	}
	return(-1);
}

int get_prev_directory(char *s)
{
	int len = ft_strlen(s) + 1;
	while(--len)
	{
		if (s[len] == '/')
			return(len);
	}
	return(-1);
}

void ft_cd(t_list **node, char **env)
{
	t_list *head;
	int i;
	int x;

	i = get_pwd(env);
	x = get_prev_directory(env[i]);
	head = *node;
	head = head->next;
	while(1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break  ;
	}
	if (head->next->tokn == END_TOKN || head->next->tokn == ST_TOKN)
	{
		env[i] = ft_strdup("PWD=");
		env[i] = ft_strjoin(env[i],get_path(env, "HOME"));
	}
	else
	{	
		if (head->next->data[0] == '/')
		{
			env[i] = ft_strdup("PWD=");
			env[i] = ft_strjoin(env[i],head->next->data);
		}
		else if (head->next->data[0] == '.' && head->next->data[1] == '.' && head->next->data[2] == '/')
		{
			env[i] = ft_strtrim(env[i],&env[i][x]);
			if (head->next->data[3])
			{
				env[i] = ft_strjoin(env[i],"/");
				env[i] = ft_strjoin(env[i],&head->next->data[3]);	
			}
		}
		else
		{
			env[i] = ft_strjoin(env[i],"/");
			env[i] = ft_strjoin(env[i],head->next->data);
		}
	}
	printf("%s\n",env[i]);
	return ;
}