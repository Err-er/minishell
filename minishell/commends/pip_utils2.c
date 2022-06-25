/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:39:30 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/25 19:56:31 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_c1(char **cmds, t_cd *cd, t_vars *var)
{
	if (!ft_strcmp(cmds[0], "export"))
	{
		ft_export (&var->node, cd);
		exit(0);
	}
	else if (!ft_strcmp(cmds[0], "unset"))
	{
		ft_unset (&var->node, cd);
		exit(0);
	}
	if (!ft_strcmp(cmds[0], "echo"))
	{
		ft_echo(var->node);
		exit(0);
	}
	else if (!ft_strcmp(cmds[0], "pwd"))
	{
		ft_getcwd(cd);
		exit(0);
	}
}

void	ft_child1(char *cmd, t_cd *cd, int *end, t_vars *var)
{
	char	*pat;
	char	**cmds;

	dup_chi1(var, end);
	cmds = ft_split_2(cmd, '\v');
	ft_check_c1(cmds, cd, var);
	if (access(cmds[0], X_OK) == 0)
		pat = cmds[0];
	else
		pat = ft_path(cd->my_env, cmd);
	if (execve(pat, cmds, cd->my_env) == -1)
	{
		perror("Error");
		exit (127);
	}
}

void	dup_chi3(t_vars *var, int *end)
{
	if (ft_check_pip2(var->node, IREDI)
		&& ft_is_last(var->node, IREDI, INPUT_H, PIPE))
	{
		dup2(var->st_in, 0);
		close(var->st_in);
		dup2(var->fd[0], var->x[0]);
		close(var->fd[0]);
	}
	if (var->fd[1])
	{
		dup2(var->fd[1], var->x[1]);
		close(var->fd[1]);
	}
	else
	{
		dup2(end[1], 1);
		close(end[0]);
		close(end[1]);
	}
}

void	ft_check_c3(char **cmds, t_cd *cd, t_vars *var)
{
	if (!ft_strcmp(cmds[0], "export"))
	{
		ft_export (&var->node, cd);
		exit(0);
	}
	else if (!ft_strcmp(cmds[0], "unset"))
	{
		ft_unset (&var->node, cd);
		exit(0);
	}
	else if (!ft_strcmp(cmds[0], "exit"))
		exit(0);
	if (!ft_strcmp(cmds[0], "echo"))
	{
		puts("here");
		ft_echo(var->node);
		exit(0);
	}
	else if (!ft_strcmp(cmds[0], "pwd"))
	{
		ft_getcwd(cd);
		exit(0);
	}
}

void	ft_child3(char *cmd, t_cd *cd, int *end, t_vars *var)
{
	char	*pat;
	char	**cmds;

	dup_chi3(var, end);
	cmds = ft_split_2(cmd, '\v');
	ft_check_c3(cmds, cd, var);
	if (access(cmds[0], X_OK) == 0)
		pat = cmds[0];
	else
		pat = ft_path(cd->my_env, cmd);
	if (execve(pat, cmds, cd->my_env) == -1)
	{
		perror("Error ");
		exit (127);
	}
}
