/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 04:26:50 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/25 00:48:15 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	treat_home(t_cd *cd)
{
	char	*temp;

	temp = ft_strtrim(get_path(cd->my_env, "HOME"), "\"");
	if (!temp)
		return (print_err("HOME", 0), 0);
	if (!access(temp, F_OK))
	{
		if (!check_per(temp))
			return (0);
		if (temp[0] == '/')
		{
			if (cd->pwd)
				free(cd->pwd);
			cd->pwd = ft_strdup("PWD=");
			cd->pwd = ft_strjoin(cd->pwd, temp);
			chdir(temp);
		}
		else
		{
			cd->pwd = ft_strjoin(cd->pwd, "/");
			cd->pwd = ft_strjoin(cd->pwd, temp);
			chdir(temp);
		}
	}
	return (free(temp), 1);
}

void	save_oldpwd(t_cd *cd)
{
	if (cd->oldpwd)
		free(cd->oldpwd);
	cd->oldpwd = ft_strdup("OLD");
	cd->oldpwd = ft_strjoin(cd->oldpwd, cd->pwd);
}

int	treat_minus(t_cd *cd)
{
	char	*temp;

	if (get_path(cd->my_env, "OLDPWD"))
	{
		free(cd->pwd);
		cd->pwd = ft_strdup("PWD=");
		temp = ft_strtrim(get_path(cd->my_env, "OLDPWD"), "\"");
		cd->pwd = ft_strjoin(cd->pwd, temp);
		printf("%s\n", get_path(cd->my_env, "OLDPWD"));
		chdir(temp);
		free(temp);
	}
	else
	{
		print_err("OLDPWD", 0);
		return (0);
	}
	return (1);
}

int	treat_prev(t_cd *cd)
{
	int		x;
	char	b[1024];

	x = get_prev_directory(cd->pwd);
	if (!getcwd(b, 1024) && x > 0 && !ft_strcmp(&cd->pwd[x], "/."))
		cd->pwd = ft_strtrim2(cd->pwd, "./");
	else if (!getcwd(b, 1024) && ft_strcmp(&cd->pwd[x], "/.."))
	{
		cd->pwd = ft_strjoin(cd->pwd, "/..");
		print_err(NULL, 3);
		return (0);
	}
	if (cd->pwd[ft_strlen(cd->pwd) - 1] == '.')
		cd->pwd = ft_strtrim2(cd->pwd, "./");
	x = get_prev_directory(cd->pwd);
	if (x > 0)
		cd->pwd = ft_substr2(cd->pwd, 0, x);
	return (1);
}

void	treat_pnt(t_cd *cd)
{
	char	b[1024];

	if (!getcwd(b, 1024))
	{
		cd->pwd = ft_strjoin(cd->pwd, "/.");
		print_err(NULL, 3);
	}
}
