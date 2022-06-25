/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 04:12:54 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/24 22:04:53 by zait-sli         ###   ########.fr       */
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

void	print_err(char *s, int er)
{
	if (er == 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(" not set\n", 2);
	}
	else if (er == 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (er == 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (er == 3)
	{
		ft_putstr_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	g_ds = 1;
}

int	check_per(char *s)
{
	if (access(s, F_OK))
	{
		print_err(s, 1);
		return (0);
	}
	else if (access(s, X_OK))
	{
		print_err(s, 2);
		return (0);
	}
	return (1);
}
