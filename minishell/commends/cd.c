/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:37:31 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/01 22:55:53 by zait-sli         ###   ########.fr       */
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

void ft_getcwd(t_cd *cd)
{
	char s[1024];
	char *ret;
	int i = get_pwd(cd->my_env);
	
	ret = getcwd(s,1024);
	while(!ret)
	{
		if (i > 0)
		{
			printf("%s\n",cd->my_env[i]);
			return ;
		}
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

int get_prev_directory(char *s)
{
	int len = ft_strlen(s) + 1;
	while(--len)
	{
		if (s[len] == '/' || s[len] == '=')
			return(len);
	}
	return(-1);
}

void ft_cd(t_list **node, t_cd *cd)
{
	t_list *head;
	int i;
	int x;
	int j=0;
	char hh[1024];
	char **t;
	char *temp;

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
		if (head->next->data[0] == '/' || (head->next->data[0] == '.' && head->next->data[1] == '.' && head->next->data[2] == '/'))
		{
			if (access(head->next->data,F_OK))
			{
				printf("minishell: cd: %s: No such file or directory\n",head->next->data);
				return ;
			}
			if (head->next->data[1])
			{
				t = ft_split_2(head->next->data,'/');
				while(t[j])
				{
					temp = ft_strdup(t[j]);
					if (j == 0)
					{	
						if (ft_strcmp(t[j],".."))
						{
							temp = ft_strdup("/");
							temp = ft_strjoin(temp,t[j]);
						}
						else
							temp = ft_strdup(t[j]);
					}
					if (x > 0 && i > 0)
					{
						if (ft_strcmp(temp,".."))
						{
							if (i > 0)
							{	
								if (j == 0)
									cd->my_env[i] = ft_strdup("PWD=");
								cd->my_env[i] = ft_strtrim(cd->my_env[i],"/");
								cd->my_env[i] = ft_strjoin(cd->my_env[i],"/");
								cd->my_env[i] = ft_strjoin(cd->my_env[i],t[j]);
							}
						}
						else
						{
							if (x > 0 && i > 0)
							{
								x = get_prev_directory(cd->my_env[i]);
								// free(cd->my_env[i]);
								cd->my_env[i] = ft_substr(cd->my_env[i],0,x);
								cd->my_env[i] = ft_strjoin(cd->my_env[i],"/");
							}
						}
					}
					if (chdir(temp))
					{
						printf("didn't work\n");
					}
					free(temp);
					j++;
				}
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
			if (i > 0 && get_path(cd->my_env, "OLDPWD"))
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
		else if (!ft_strcmp(head->next->data,".."))
		{
			if (x > 0 && i > 0 && ft_strcmp(cd->my_env[i],"PWD=/"))
				ft_strlcpy(cd->my_env[i],cd->my_env[i],x+1);
			chdir("..");
		}
		else
		{
			if (!access(head->next->data,F_OK) && !access(head->next->data,X_OK))
			{
				if (i > 0)
				{
					cd->my_env[i] = ft_strjoin(cd->my_env[i],"/");
					cd->my_env[i] = ft_strjoin(cd->my_env[i],ft_strtrim(head->next->data,"/"));
				}
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
				return ;
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