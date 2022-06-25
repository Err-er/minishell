/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:38:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/25 19:57:04 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fre(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
}

void	print_error_p(char **cmd)
{
	ft_putstr_fd("minishell : command not found: ", 2);
	cmd[0] = ft_strtrim(cmd[0], " ");
	if (cmd[0])
		ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	ft_fre(cmd);
	exit(127);
}

void	ft_f(char **p, char **cmd)
{
	ft_fre(cmd);
	ft_fre(p);
}

char	*ft_path(char **env, char *cd)
{
	int		i;
	char	*str;
	char	*str2;
	char	**p;
	char	**cmd;

	str = get_path(env, "PATH");
	p = ft_split(str, ':');
	cmd = ft_split_2(cd, '\v');
	if (access(cmd[0], X_OK) == 0)
		return (ft_f(p, cmd), cd);
	if (!cmd || !str)
		print_error_p(cmd);
	i = -1;
	while (p[++i])
	{
		str2 = ft_strjoin(p[i], cmd[0]);
		if (access(str2, X_OK) == 0)
			return (ft_fre(cmd), str2);
		free(str2);
	}
	print_error_p(cmd);
	return (NULL);
}

void	dup_chi1(t_vars *var, int *end)
{
	if (ft_check_pip2(var->node, IREDI)
		&& ft_is_last(var->node, IREDI, INPUT_H, PIPE))
	{
		dup2(var->st_in, 0);
		close(var->st_in);
		dup2(var->fd[0], var->x[0]);
		close(var->fd[0]);
	}
	if (!var->c2)
	{
		dup2(end[1], 1);
		close(end[0]);
		close(end[1]);
	}
	if (ft_check_pip2(var->node, OREDI) || ft_check_pip2(var->node, OUTPUT_H))
	{
		dup2(var->fd[1], var->x[1]);
		close(var->fd[1]);
	}
}
