/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:22:23 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/21 12:55:26 by asabbar          ###   ########.fr       */
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
void	waitp(char **cmd, int id)
{
	int	i;

	i = -1;
	while (cmd[++i])
		waitpid(id, NULL, 0);
	ft_fre(cmd);
}

char	*ft_path(char **env, char *cd)
{
	int		i;
	char	*str;
	char	*str2;
	char	**p;
	char	**cmd;

    if(access(cd, X_OK) == 0)
        return (cd);
	str = get_path(env, "PATH");
	p = ft_split(str, ':');
    cmd = ft_split_2(cd, '&');
	i = -1;
	while (p[++i])
	{
		str2 = ft_strjoin(p[i], cmd[0]);
		if (access(str2, X_OK) == 0)
		{
			ft_fre(cmd);
			return (str2);
		}
		free(str2);
	}
	printf("error --> command not found: ");
	printf("%s", cmd[0]);
	printf("\n");
	ft_fre(cmd);
	exit(1);
}
void	ft_child1(char *cmd, char **env, int *end, t_list *node)
{
	char	*pat;
	char	**cmds;

	pat = ft_path(env, cmd);
	cmds = ft_split_2(cmd, '&');
	close(end[0]);
	dup2(end[1], 1);
	if(!ft_strcmp(cmds[0], "echo"))
	{
		ft_echo(node);
		exit(0);
	}
	else if (execve(pat, cmds, env) == -1)
	{
		printf("error in ft_child1\n");
		exit (1);
	}
}

void	ft_child3(char *cmd, char **env, int *end, t_list *node)
{
	char	*pat;
	char	**cmds;

	pat = ft_path(env, cmd);
    cmds = ft_split_2(cmd, '&');
	close(end[0]);
	dup2(end[1], 1);
	if(!ft_strcmp(cmds[0], "echo"))
	{
		ft_echo(node);
		exit(0);
	}
	else if (execve(pat, cmds, env) == -1)
	{
		printf("error in ft_child3\n");
		exit (1);
	}
}

void	ft_child2(char *cmds, char **env, t_list *node)
{
	char	*pat;
	char	**cmd;

	pat = ft_path(env, cmds);
	cmd = ft_split_2(cmds, '&');
	if(!ft_strcmp(cmd[0], "echo"))
	{
		ft_echo(node);
		exit(0);
	}
	else if (execve(pat, cmd, env) == -1)
	{
		printf("error in ft_child2\n");
		exit (1);
	}
}

int	forkpipe(int *end)
{
	int	id;

	pipe(end);
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

int	is2or1(int i)
{
	if ((i % 2) == 0)
		return (1);
	else
		return (0);
}

int	ft_cheak(int i, char **cmd)
{
	if (!is2or1(i))
	{
		if (!cmd[i + 1])
			return (2);
		else
			return (3);
	}
	else if (is2or1(i))
	{
		if (!cmd[i + 1])
			return (2);
		else
			return (3);
	}
	return (0);
}

void    c_pip(char **str, char **env, t_list *node)
{
	int		end[2];
	int		id;
	int		id1;
	int		i;

	// i = -1;
	// while(str[i])
	// 	i++;
	// id  = malloc(i * sizeof(int));
	i = -1;
	while (str[++i])
	{
		id = forkpipe(end);
		if (id == -1)
			exit(1);
		else if (id == 0)
		{
			if (i == 0)
				ft_child1(str[i], env, end, node);
			else if (ft_cheak(i, str) == 2)
				ft_child2(str[i], env, node);
			else if (ft_cheak(i, str) == 3)
				ft_child3(str[i], env, end, node);
		}
		if(i == 0)
			id1 = id;
	    close(end[1]);
        dup2(end[0], 0);
	    close(end[0]);
	}
	waitpid(id1, NULL, 0);
	// while (str[--i])
	// 	waitpid(id, NULL, 0);
	// waitp(str, id);
}