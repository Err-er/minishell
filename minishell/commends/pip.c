/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:22:23 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/24 05:45:19 by zait-sli         ###   ########.fr       */
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

	str = get_path(env, "PATH");
	p = ft_split(str, ':');
    cmd = ft_split_2(cd, '\v');
	if (!cmd[0])
		exit(0);
	if(access(cmd[0], X_OK) == 0)
        return (cmd[0]);
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
	printf("minishell : command not found: ");
	printf("%s", cmd[0]);
	printf("\n");
	ft_fre(cmd);
	exit(1);
}
void	ft_child1(char *cmd, char **env, int *end, t_list **node)
{
	char	*pat;
	char	**cmds;

	pat = ft_path(env, cmd);
	cmds = ft_split_2(cmd, '\v');
	dup2(end[1], 1);
	close(end[0]);
	close(end[1]);
	if(!ft_strcmp(cmds[0], "echo"))
	{
		ft_echo(node);
		exit(0);
	}
	if(!ft_strcmp(cmd, "cd"))
	{
		ft_cd(node,env);
		exit(0);
	}
	else if (execve(pat, cmds, env) == -1)
	{
		// printf("error in ft_child1\n");
		perror("Error");
		exit (1);
	}
}

void	ft_child3(char *cmd, char **env, int *end, t_list **node)
{
	char	*pat;
	char	**cmds;

	pat = ft_path(env, cmd);
    cmds = ft_split_2(cmd, '\v');
	dup2(end[1], 1);
	close(end[0]);
	close(end[1]);
	if(!ft_strcmp(cmd, "cd"))
	{
		ft_cd(node,env);
		exit(0);
	}
	if(!ft_strcmp(cmds[0], "echo"))
	{
		ft_echo(node);
		exit(0);
	}
	else if (execve(pat, cmds, env) == -1)
	{
		perror("Error ");
		exit (1);
	}
}

void	ft_child2(char *cmds, char **env, t_list **node)
{
	char	*pat;
	char	**cmd;

	pat = ft_path(env, cmds);
	cmd = ft_split_2(cmds, '\v');
	if(!ft_strcmp(cmd[0], "echo"))
	{
		ft_echo(node);
		exit(0);
	}
	if(!ft_strcmp(cmd[0], "cd"))
	{
		ft_cd(node,env);
		exit(0);
	}
	else if(!ft_strcmp(cmd[0], "pwd"))
	{
		printf("%s\n", get_path(env, "PWD"));
		exit(0);
	}
	else if (execve(pat, cmd, env) == -1)
	{
		perror("Error ");
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

void ft_change_node(t_list **node, char *str)
{
	char	**s;

	s = ft_split_2(str, '\v');
	if(!ft_strcmp(s[0], "echo"))
	{
		while(ft_strcmp((*node)->data, "echo"))
			(*node) = (*node)->next;
		(*node) = (*node)->next;
	}
}
void    c_pip(char **str, char **env, t_list *node)
{
	int		end[2];
	int		*id;
	int		c;
	int		i;

	i = -1;
	while (str[++i]);
	id = malloc(i * sizeof(int));
	i = -1;
	while (str[++i])
	{
		id[i] = forkpipe(end);
		if (id[i] == -1)
			exit(1);
		else if (id[i] == 0)
		{
			if (i == 0)
				ft_child1(str[i], env, end, &node);
			else if (ft_cheak(i, str) == 2)
				ft_child2(str[i], env, &node);
			else if (ft_cheak(i, str) == 3)
				ft_child3(str[i], env, end, &node);
		}
		if (i == 0)
			c = id[i];
		ft_change_node(&node , str[i]);
        dup2(end[0], 0);
	    close(end[1]);
	    close(end[0]);
	}
	while(i)
	{
		waitpid(id[i], NULL, 0);
		i--;
	}
	waitpid(c, NULL, 0);
	ft_fre(str);
}