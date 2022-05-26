/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:37:31 by zait-sli          #+#    #+#             */
/*   Updated: 2022/05/26 00:20:47 by zait-sli         ###   ########.fr       */
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

void ft_cd(t_list **node, t_cd *cd)
{
	t_list *head;
	int i;
	int x;
	char hh[100];

	i = get_pwd(cd->my_env);
	x = get_prev_directory(cd->my_env[i]);
	head = *node;
	head = head->next;
	// if (*cd->oldpwd)
	// 	free(cd->oldpwd);
	cd->oldpwd = ft_strdup("OLD");
	cd->oldpwd = ft_strjoin(cd->oldpwd,cd->my_env[i]);
	while(1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break  ;
	}
	if (head->next->tokn == END_TOKN || head->next->tokn == ST_TOKN)
	{
		return ;
		// cd->my_env[i] = ft_strdup("PWD=");
		// cd->my_env[i] = ft_strjoin(cd->my_env[i],get_path(cd->my_env, "HOME"));
	}
	else
	{	
		if (head->next->data[0] == '/')
		{
			cd->my_env[i] = ft_strdup("PWD=");
			cd->my_env[i] = ft_strjoin(cd->my_env[i],head->next->data);
			// printf("%s\n",getcwd(hh,100));
			if (chdir(head->next->data))
				printf("didn't work\n");
		}
		else if (head->next->data[0] == '.' && head->next->data[1] == '.' && head->next->data[2] == '/')
		{
			ft_strlcpy(cd->my_env[i],cd->my_env[i],x);
			if (chdir(".."))
				printf("didn't work\n");
			if (head->next->data[3])
			{
				cd->my_env[i] = ft_strjoin(cd->my_env[i],"/");
				cd->my_env[i] = ft_strjoin(cd->my_env[i],&head->next->data[3]);	
				chdir(&head->next->data[3]);
			}
		}
		else if (head->next->data[0] == '.' && head->next->data[1] == '.'){
			
			ft_strlcpy(cd->my_env[i],cd->my_env[i],x);
			chdir("..");
		}
		else
		{
			if (!access(head->next->data,F_OK) && !access(head->next->data,X_OK))
			{
				cd->my_env[i] = ft_strjoin(cd->my_env[i],"/");
				cd->my_env[i] = ft_strjoin(cd->my_env[i],head->next->data);
				chdir(head->next->data);	
			}
			else if (access(head->next->data,X_OK))
			{
				printf("minishell: cd: %s: Permission denied\n",head->next->data);
			}
			else
			{
				printf("minishell: cd: %s: No such file or directory\n",head->next->data);
				return ;
			}
		}
	}
	cd->my_env[i+1] = ft_strdup(cd->oldpwd);
	return ;
}