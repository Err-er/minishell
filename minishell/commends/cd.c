/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:37:31 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/22 22:39:52 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4))
			i++;
		else
			return (i);
	}
	return (-1);
}

void	ft_getcwd(t_cd *cd)
{
	char	s[1024];
	char	*ret;
	int		i;

	if (cd->pwd)
	{
		printf("%s\n", &cd->pwd[4]);
		return ;
	}
	i = get_pwd(cd->my_env);
	ret = getcwd(s, 1024);
	while (!ret)
	{
		if (i > 0)
		{
			printf("%s\n", cd->my_env[i]);
			return ;
		}
		chdir("..");
		ret = getcwd(s, 1024);
		if (ret)
		{
			printf("%s\n", ret);
			return ;
		}
	}
	printf("%s\n", ret);
}

int	get_prev_directory(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (s[len] == '/' && s[len - 1] == '=')
		return (len);
	else if (s[len] == '/' && s[len - 1] != '=')
	{
		len -= 1;
	}
	while (len)
	{
		len--;
		if (s[len] == '/' && s[len -1] == '=')
			return (len + 1);
		else if (s[len] == '/' || s[len] == '=')
			return (len);
	}
	return (-1);
}

void	ft_cd(t_list **node, t_cd *cd)
{
	t_list	*head;
	int		i;
	int		x;
	int		j;
	char	**t;
	char	*temp;
	char	buff[1024];

	j = 0;
	head = *node;
	head = head->next;
	i = get_pwd(cd->my_env);
	if (i > 0)
		x = get_prev_directory(cd->my_env[i]);
	else
		x = -1;
	if (i > 0)
	{
		if (cd->oldpwd)
			free(cd->oldpwd);
		cd->oldpwd = ft_strdup("OLD");
		cd->oldpwd = ft_strjoin(cd->oldpwd, cd->my_env[i]);
	}
	while (1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break ;
	}
	if (!head->next->data)
		return ;
	if (head->next->tokn == END_TOKN || head->next->tokn == ST_TOKN)
	{
		temp = ft_strtrim(get_path(cd->my_env, "HOME"), "\"");
		if (!temp)
		{
			g_ds = 1;
			printf("HOME not set\n");
			return ;
		}
		if (access(temp, F_OK))
		{
			g_ds = 1;
			printf("minishell: cd: %s: No such file or directory\n", temp);
			return ;
		}
		else if (access(temp, X_OK))
		{
			g_ds = 1;
			printf("minishell: cd: %s: Permission denied\n", temp);
			return ;
		}
		if (!access(temp, F_OK))
		{
			if (temp[0] == '/')
			{
				if (cd->pwd)
					free(cd->pwd);
				cd->pwd = ft_strdup("PWD=");
				cd->pwd = ft_strjoin(cd->pwd, temp);
				if (i > 0)
				{
					free(cd->my_env[i]);
					cd->my_env[i] = ft_strdup("PWD=");
					cd->my_env[i] = ft_strjoin(cd->my_env[i], temp);
				}
				chdir(temp);
			}
			else
			{
				cd->pwd = ft_strjoin(cd->pwd, "/");
				cd->pwd = ft_strjoin(cd->pwd, temp);
				if (i > 0)
				{
					cd->my_env[i] = ft_strjoin(cd->my_env[i], "/");
					cd->my_env[i] = ft_strjoin(cd->my_env[i], temp);
				}
				chdir(temp);
			}
		}
		free(temp);
	}
	else if (head->next->data[0] == '-')
	{
		if (i > 0 && get_path(cd->my_env, "OLDPWD"))
		{
			free(cd->pwd);
			cd->pwd = ft_strdup("PWD=");
			temp = ft_strtrim(get_path(cd->my_env, "OLDPWD"), "\"");
			cd->pwd = ft_strjoin(cd->pwd, temp);
			free(cd->my_env[i]);
			cd->my_env[i] = ft_strdup("PWD=");
			cd->my_env[i] = ft_strjoin(cd->my_env[i],
					get_path(cd->my_env, "OLDPWD"));
			free(temp);
		}
		if (get_path(cd->my_env, "OLDPWD"))
		{	
			printf("%s\n", get_path(cd->my_env, "OLDPWD"));
			temp = ft_strtrim(get_path(cd->my_env, "OLDPWD"), "\"");
			chdir(temp);
			free(temp);
		}
		else
		{
			g_ds = 1;
			printf("minishell: cd: OLDPWD not set\n");
			return ;
		}
	}
	else
	{
		if (access(head->next->data, F_OK))
		{
			g_ds = 1;
			printf("minishell: cd: %s: No such file or directory\n",
				head->next->data);
			return ;
		}
		else if (access(head->next->data, X_OK))
		{
			g_ds = 1;
			printf("minishell: cd: %s: Permission denied\n", head->next->data);
			return ;
		}
		t = ft_split_2(head->next->data, '/');
		while (t[j])
		{
			temp = ft_strdup(t[j]);
			if (!ft_strcmp(temp, ".."))
			{
				x = get_prev_directory(cd->pwd);
				if (!getcwd(buff, 1024) && x > 0 && !ft_strcmp(&cd->pwd[x], "/."))
					cd->pwd = ft_strtrim2(cd->pwd, "./");
				else if (!getcwd(buff, 1024) && ft_strcmp(&cd->pwd[x], "/.."))
				{
					cd->pwd = ft_strjoin(cd->pwd, "/..");
					ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
					return ;
				}
				if (cd->pwd[ft_strlen(cd->pwd) - 1] == '.')
					cd->pwd = ft_strtrim2(cd->pwd, "./");
				x = get_prev_directory(cd->pwd);
				if (x > 0)
					cd->pwd = ft_substr2(cd->pwd, 0, x);
				x = get_prev_directory(cd->my_env[i]);
				if (x > 0 && i > 0)
				{
					free(cd->my_env[i]);
					cd->my_env[i] = ft_strdup(cd->pwd);
				}
			}
			else if (!ft_strcmp(temp, "."))
			{
				if (!getcwd(buff, 1024))
				{
					cd->pwd = ft_strjoin(cd->pwd, "/.");
					ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
				}
			}
			else
			{
				if (j == 0 && head->next->data[0] == '/')
				{
					if (cd->pwd)
						free(cd->pwd);
					cd->pwd = ft_strdup("PWD=");
				}
				cd->pwd = ft_strtrim2(cd->pwd, "/");
				cd->pwd = ft_strjoin(cd->pwd, "/");
				cd->pwd = ft_strjoin(cd->pwd, t[j]);
				if (i > 0)
				{	
					free(cd->my_env[i]);
					cd->my_env[i] = ft_strdup(cd->pwd);
				}
			}
			chdir(temp);
			free(temp);
			j++;
		}
		ft_fre(t);
	}
	if (get_path(cd->my_env, "OLDPWD"))
		replace_this(cd, cd->oldpwd);
	else if (!get_path(cd->my_env, "OLDPWD") && get_path(cd->my_env, "PWD"))
	{
		export_this(cd, cd->oldpwd);
	}
	g_ds = 0;
	return ;
}
