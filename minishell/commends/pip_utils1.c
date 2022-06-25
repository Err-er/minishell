/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:39:55 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/25 19:56:12 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_chi2(t_vars *var)
{
	if (ft_check_pip2(var->node, IREDI)
		&& ft_is_last(var->node, IREDI, INPUT_H, PIPE))
	{
		dup2(var->st_in, 0);
		close(var->st_in);
		dup2(var->fd[0], var->x[0]);
		close(var->fd[0]);
	}
	if (ft_check_pip2(var->node, OREDI) || ft_check_pip2(var->node, OUTPUT_H))
	{
		dup2(var->fd[1], var->x[1]);
		close(var->fd[1]);
	}
}

void	ft_check_c2(char **cmd, t_cd *cd, t_vars *var)
{
	if (!ft_strcmp(cmd[0], "export"))
	{
		ft_export(&var->node, cd);
		exit(0);
	}
	if (!ft_strcmp(cmd[0], "unset"))
	{
		ft_unset(&var->node, cd);
		exit(0);
	}
	if (!ft_strcmp(cmd[0], "exit"))
	{
		exit(0);
	}
	if (!ft_strcmp(cmd[0], "echo"))
	{
		ft_echo(var->node);
		exit(0);
	}
	else if (!ft_strcmp(cmd[0], "pwd"))
	{
		ft_getcwd(cd);
		exit(0);
	}
}

void	ft_child2(char *cmds, t_cd *cd, t_vars *var)
{
	char	*pat;
	char	**cmd;

	dup_chi2(var);
	cmd = ft_split_2(cmds, '\v');
	ft_check_c2(cmd, cd, var);
	if (access(cmd[0], X_OK) == 0)
		pat = cmd[0];
	else
		pat = ft_path(cd->my_env, cmds);
	if (execve(pat, cmd, cd->my_env) == -1)
	{
		perror("Error ");
		exit (127);
	}
}

int	forkpipe(int *end)
{
	int	id;

	if (pipe(end) == -1)
	{
		printf("error pipe\n");
		return (-1);
	}
	id = fork();
	if (id == -1)
	{
		printf("error fork\n");
		return (-1);
	}
	return (id);
}

int	ft_cheak(int i, char **cmd)
{
	if (!cmd[i + 1])
		return (2);
	else
		return (3);
	return (0);
}
