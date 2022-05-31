/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:37:31 by zait-sli          #+#    #+#             */
/*   Updated: 2022/05/31 09:33:13 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_getcwd(void)
{
	char s[1024];
	char *ret;
	
	ret = getcwd(s,1024);
	while(!ret)
	{
		chdir("..");
		ret = getcwd(s,1024);
		if (ret)
		{
			printf("%s\n",ret);
			return ;
		}
	}
	printf("%s\n",ret);
}

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
	char hh[1024];

	head = *node;
	head = head->next;
	i = get_pwd(cd->my_env);
	if (i > 0)
		x = get_prev_directory(cd->my_env[i]);
	else
		x = -1;
	if (i > 0)
	{
		cd->oldpwd = ft_strdup("OLD");
		cd->oldpwd = ft_strjoin(cd->oldpwd,cd->my_env[i]);
	}
	while(1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break  ;
	}
	if (head->next->tokn == END_TOKN || head->next->tokn == ST_TOKN)
	{
		if (!get_path(cd->my_env, "HOME"))
			printf("HOME not set\n");
		if (i > 0)
		{
			cd->my_env[i] = ft_strdup("PWD=");
			cd->my_env[i] = ft_strjoin(cd->my_env[i],get_path(cd->my_env, "HOME"));
		}
		chdir(get_path(cd->my_env, "HOME"));
	}
	else
	{	
		if (head->next->data[0] == '/')
		{
			printf("here0\n");
			if (head->next->data[0] == '/' && head->next->data[1] == '.' && head->next->data[2] == '.')
			{
				if (x > 0){
				cd->my_env[i] = ft_strdup("PWD=");
				cd->my_env[i] = ft_strjoin(cd->my_env[i],"/");
				}
				if (chdir(head->next->data))
					printf("didn't work\n");
			}
			else
			{
				if (i > 0)
				{
					cd->my_env[i] = ft_strdup("PWD=");
					cd->my_env[i] = ft_strjoin(cd->my_env[i],head->next->data);	
				}
				chdir(head->next->data);
			}
		}
		else if (head->next->data[0] == '-')
		{
			if (i > 0)
			{
				free(cd->my_env[i]);
				cd->my_env[i] = ft_strdup("PWD=");
				cd->my_env[i] = ft_strjoin(cd->my_env[i],get_path(cd->my_env, "OLDPWD"));
			}
			if (get_path(cd->my_env, "OLDPWD"))
			{	
				printf("%s\n",get_path(cd->my_env, "OLDPWD"));
				if (chdir(get_path(cd->my_env, "OLDPWD")))
					printf("didn't work\n");
			}
			else
				printf("minishell: cd: OLDPWD not set\n");
		}
		else if (head->next->data[0] == '.' && head->next->data[1] == '.' && head->next->data[2] == '/')
		{
			if (i > 0 && x > 0)
				ft_strlcpy(cd->my_env[i],cd->my_env[i],x);
			chdir("..");
			if (head->next->data[3])
			{
				chdir(&head->next->data[3]);
				cd->my_env[i] = ft_strjoin(cd->my_env[i],"/");
				cd->my_env[i] = ft_strjoin(cd->my_env[i],&head->next->data[3]);	
			}
		}
		else if (!ft_strcmp(head->next->data,".."))
		{
			if (x > 0 && i > 0)
				ft_strlcpy(cd->my_env[i],cd->my_env[i],x+1);
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
			else if (access(head->next->data,F_OK))
			{
				printf("minishell: cd: %s: No such file or directory\n",head->next->data);
				return ;
			}
			else if (access(head->next->data,X_OK))
			{
				printf("minishell: cd: %s: Permission denied\n",head->next->data);
			}
		}
	}
	if (get_path(cd->my_env, "OLDPWD"))
		cd->my_env[i+1] = ft_strdup(cd->oldpwd);
	else if (!get_path(cd->my_env, "OLDPWD") && get_path(cd->my_env, "PWD"))
	{
		export_this(cd,"OLDPWD");
		cd->my_env[i+1] = ft_strdup(cd->oldpwd);
	}
	return ;
}