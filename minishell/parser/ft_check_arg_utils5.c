/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_utils5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/26 13:14:27 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_pip_utils(t_list *head, char *str)
{
	head = head->next;
	while (head)
	{
		ft_pip_utils_1(&head, &str);
		ft_pip_utils_2(&head, &str);
		if (head->tokn == IREDI)
		{
			head = head->next;
			if (head->tokn == WS)
				head = head->next;
			while (head->tokn == WR && head->tokn != END_TOKN)
				head = head->next;
		}
		else if (head->tokn == 0 || head->tokn == LIMITER)
			head = head->next;
	}
	return (str);
}

int	ft_pip(t_list *node, t_cd *cd)
{
	char	*str;
	char	**s;

	str = ft_strdup("");
	str = ft_pip_utils(node, str);
	str = ft_strjoin(str, "\v");
	s = ft_split_2(str, '\t');
	free(str);
	return (c_pip(s, cd, node));
}

int	ft_dup_ex(t_vars var, int *end)
{
	if (ft_check_pip(var.node, INPUT_H))
	{
		if (!ft_is_last(var.node, INPUT_H, IREDI, END_TOKN))
		{
			dup2(var.fd[0], var.x[0]);
			close(var.fd[0]);
		}
		else
		{
			if (pipe(end) == -1)
				perror("Error");
			ft_putstr_fd(var.value, end[1]);
			close(end[1]);
			dup2(end[0], 0);
			close(end[0]);
		}
	}
	else if (var.fd[0])
	{
		dup2(var.fd[0], var.x[0]);
		close(var.fd[0]);
	}
	if (var.fd[1])
		return (dup2(var.fd[1], var.x[1]), close(var.fd[1]), 1);
	return (1);
}

int	ft_ex_cmd(char *cmd, t_cd *cd, t_vars var)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(var.node), 0);
	else if (!ft_strcmp(cmd, "export"))
		return (ft_export(&var.node, cd), 0);
	else if (!ft_strcmp(cmd, "exit"))
		return (0);
	else if (!ft_strcmp(cmd, "unset"))
		return (ft_unset(&var.node, cd), 0);
	else if (!ft_strcmp(cmd, "pwd"))
		return (ft_getcwd(cd), 0);
	else if (!ft_strcmp(cmd, "env"))
		return (ft_env(&var.node, cd), 0);
	return (1);
}

void	ft_ex(char *cmds, t_cd *cd, t_vars var)
{
	char	*pat;
	char	**cmd;
	int		end[2];

	cmd = ft_split_2(cmds, '\v');
	ft_dup_ex(var, end);
	if (!ft_ex_cmd(cmd[0], cd, var))
		exit(0);
	if (access(cmd[0], X_OK) == 0)
		pat = cmd[0];
	else
		pat = ft_path(cd->my_env, cmds);
	if (execve(pat, cmd, cd->my_env) == -1)
	{
		perror("Error ");
		exit (126);
	}
}
