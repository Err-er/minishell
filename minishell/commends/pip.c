/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:22:23 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/05 13:08:54 by asabbar          ###   ########.fr       */
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
	if (access(cmd[0], X_OK) == 0)
	{
		ft_fre(cmd);
		ft_fre(p);
		return (cmd[0]);
	}
	if (!cmd)
	{
		ft_putstr_fd("minishell : command not found: ", 2);
		if (cmd[0])
			ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		ft_fre(cmd);
		exit(127);
	}
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
	ft_putstr_fd("minishell : command not found: ", 2);
	if (cmd[0])
		ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	ft_fre(cmd);
	exit(127);
}

void	ft_child1(char *cmd, t_cd *cd, int *end, t_vars var)
{
	char	*pat;
	char	**cmds;
	char	hh[100];

	if (ft_check_pip2(var.node, IREDI) && ft_is_last(var.node, IREDI, INPUT_H, PIPE))
	{
		dup2(var.st_in, 0);
		close(var.st_in);
		dup2(var.fd[0], var.x[0]);
		close(var.fd[0]);
	}
	if (!var.c2)
	{
		dup2(end[1], 1);
		close(end[0]);
		close(end[1]);
	}
	if (ft_check_pip2(var.node, OREDI) || ft_check_pip2(var.node, OUTPUT_H))
	{
		dup2(var.fd[1], var.x[1]);
		close(var.fd[1]);
	}
	cmds = ft_split_2(cmd, '\v');
	if (!ft_strcmp(cmds[0], "export"))
	{
		ft_exprot (&var.node, cd);
		exit(0);
	}
	else if (!ft_strcmp(cmds[0], "unset"))
	{
		ft_unset (&var.node, cd);
		exit(0);
	}
	pat = ft_path(cd->my_env, cmd);
	if (access(cmds[0], X_OK) == 0)
		pat = cmds[0];
	if (!ft_strcmp(cmds[0], "echo"))
	{
		ft_echo(var.node);
		exit(0);
	}
	else if (!ft_strcmp(cmds[0], "pwd"))
	{
		printf("%s\n", getcwd(hh, 100));
		exit(0);
	}
	if (execve(pat, cmds, cd->my_env) == -1)
	{
		perror("Error");
		exit (127);
	}
}

void	ft_child3(char *cmd, t_cd *cd, int *end, t_vars var)
{
	char	*pat;
	char	**cmds;
	char	hh[100];

	if (ft_check_pip2(var.node, IREDI) && ft_is_last(var.node, IREDI, INPUT_H, PIPE))
	{
		dup2(var.st_in, 0);
		close(var.st_in);
		dup2(var.fd[0], var.x[0]);
		close(var.fd[0]);
	}
	if (ft_check_pip2(var.node, OREDI) || ft_check_pip2(var.node, OUTPUT_H))
	{
		dup2(var.fd[1], var.x[1]);
		close(var.fd[1]);
	}
	else
	{
		dup2(end[1], 1);
		close(end[0]);
		close(end[1]);
	}
	cmds = ft_split_2(cmd, '\v');
	if (!ft_strcmp(cmds[0], "export"))
	{
		ft_exprot (&var.node, cd);
		exit(0);
	}
	else if (!ft_strcmp(cmds[0], "unset"))
	{
		ft_unset (&var.node, cd);
		exit(0);
	}
	else if (!ft_strcmp(cmds[0], "exit"))
		exit(0);
	pat = ft_path(cd->my_env, cmd);
	if (access(cmds[0], X_OK) == 0)
		pat = cmds[0];
	if (!ft_strcmp(cmds[0], "echo"))
	{
		puts("here");
		ft_echo(var.node);
		exit(0);
	}
	else if (!ft_strcmp(cmds[0], "pwd"))
	{
		printf("%s\n", getcwd(hh, 100));
		exit(0);
	}
	if (execve(pat, cmds, cd->my_env) == -1)
	{
		perror("Error ");
		exit (127);
	}
}

void	ft_child2(char *cmds, t_cd *cd, t_vars var)
{
	char	*pat;
	char	**cmd;
	char	hh[100];
	int		end[2];

	if (ft_check_pip2(var.node, IREDI)
		&& ft_is_last(var.node, IREDI, INPUT_H, PIPE))
	{
		dup2(var.st_in, 0);
		close(var.st_in);
		dup2(var.fd[0], var.x[0]);
		close(var.fd[0]);
	}
	if (ft_check_pip2(var.node, OREDI) || ft_check_pip2(var.node, OUTPUT_H))
	{
		dup2(var.fd[1], var.x[1]);
		close(var.fd[1]);
	}
	cmd = ft_split_2(cmds, '\v');
	if (!ft_strcmp(cmd[0], "export"))
	{
		ft_exprot(&var.node, cd);
		exit(0);
	}
	if (!ft_strcmp(cmd[0], "unset"))
	{
		ft_unset(&var.node, cd);
		exit(0);
	}
	if (!ft_strcmp(cmd[0], "exit"))
	{
		exit(0);
	}
	pat = ft_path(cd->my_env, cmds);
	if (access(cmd[0], X_OK) == 0)
		pat = cmd[0];
	if (!ft_strcmp(cmd[0], "echo"))
	{
		ft_echo(var.node);
		exit(0);
	}
	else if (!ft_strcmp(cmd[0], "pwd"))
	{
		printf("%s\n", getcwd(hh, 100));
		exit(0);
	}
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

void ft_change_node(t_list **node)
{
	while ((*node)->tokn != PIPE && (*node))
	{
		if ((*node)->next->tokn == END_TOKN)
			break ;
		(*node) = (*node)->next;
	}
	(*node) = (*node)->next;
}

int	ft_check_red(t_list *node, int fd)
{
	int	c; 
	int	i;

	while (node->tokn != PIPE)
	{
		if (node->tokn == OREDI)
		{
			node = node->next;
			fd = open(node->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
				i = 1;
		}
		else if (node->tokn == IREDI)
		{
			node = node->next;
			fd = open(node->data, O_RDONLY);
				i = 0;
		}
		node = node->next;
	}
	return (i);
}

int	ft_check_red2(t_list *node, int fd)
{
	while (node->tokn != PIPE && node)
	{
		if (node->tokn == OREDI)
		{
			node = node->next;
			fd = open(node->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
		}
		else if (node->tokn == IREDI)
		{
			node = node->next;
			fd = open(node->data, O_RDONLY);
		}
		node = node->next;
	}
	return (fd);
}

void	c_pip(char **str, t_cd *cd, t_list *node)
{
	t_vars	var;
	int		end[2];
	char	*p;
	int		i;
	t_list	*head;

	i = 0;
	var.file_n = ft_strdup("");
	var.value = ft_strdup("");
	while (str[i])
		i++;
	var.id = malloc(i * sizeof(int));
	i = -1;
	var.st_in = dup(0);
	while (str[++i])
	{
		var.node = node;
		var.c = 0;
		var.c2 = 0;
		head = node;
		while (head && head->tokn != PIPE)
		{
			if (head->tokn == OREDI)
			{
				var.file_n = ft_strdup("");
				head = head->next;
				if (head->tokn == WS)
					head = head->next;
				while (head->tokn == WR && head->tokn != END_TOKN)
				{
					var.file_n = ft_strjoin_nf(var.file_n, head->data);
					head = head->next;
				}
				var.fd[1] = open(var.file_n, O_CREAT | O_RDWR | O_TRUNC, 0666);
				if (var.fd[1] == -1)
				{
					perror("Error");
					break ;
				}
				free(var.file_n);
				var.x[1] = 1;
			}
			else if (head->tokn == OUTPUT_H)
			{
				var.file_n = ft_strdup("");
				head = head->next;
				if (head->tokn == WS && head->tokn != END_TOKN)
					head = head->next;
				while (head->tokn == WR && head->tokn != END_TOKN)
				{
					var.file_n = ft_strjoin_nf(var.file_n, head->data);
					head = head->next;
				}
				var.fd[1] = open(var.file_n,
						O_CREAT | O_WRONLY | O_APPEND, 0777);
				if (var.fd[1] == -1)
				{
					perror("Error");
					break ;
				}
				free(var.file_n);
				var.x[1] = 1;
			}
			else if (head->tokn == INPUT_H)
			{
				var.value = ft_strdup("");
				head = head->next;
				while (head->tokn == WS && head->tokn != END_TOKN)
					head = head->next;
				dup2(var.st_in, 0);
				while (1)
				{
					p = readline("> ");
					if (!ft_strcmp2(p, head->data))
						break ;
					p = ft_strjoin_nf(p, "\n");
					var.value = ft_strjoin(var.value, p);
					free(p);
				}
			}
			else if (head->tokn == IREDI)
			{
				var.file_n = ft_strdup("");
				head = head->next;
				if (head->tokn == WS)
					head = head->next;
				while (head->tokn == WR && head->tokn != END_TOKN)
				{
					var.file_n = ft_strjoin(var.file_n, head->data);
					head = head->next;
				}
				var.fd[0] = open(var.file_n, O_RDONLY);
				if (var.fd[0] == -1 || !var.file_n)
				{
					perror("Error");
					break ;
				}
				free(var.file_n);
				var.x[0] = 0;
			}
			else
				head = head->next;
		}
		if (ft_check_pip2(node, INPUT_H) && var. value)
		{
			if (pipe(end) == -1)
				perror("Error");
			ft_putstr_fd(var.value, end[1]);
			close(end[1]);
			dup2(end[0], 0);
			close(end[0]);
		}
		var.id[i] = forkpipe(end);
		if (var.id[i] == -1)
			exit(127);
		if (var.id[i] == 0)
		{
			if (!str[i + 1])
				var.c2 = 1;
			if (i == 0)
				ft_child1(str[i], cd, end, var);
			else if (ft_cheak(i, str) == 2)
				ft_child2(str[i], cd, var);
			else if (ft_cheak(i, str) == 3)
				ft_child3(str[i], cd, end, var);
		}
		if (i == 0 && !ft_check_pip2(node, INPUT_H))
			var.c = var.id[i];
		ft_change_node(&node);
		dup2(end[0], 0);
		close(end[1]);
		close(end[0]);
		var.fd[0] = 0;
		var.fd[1] = 0;
	}
	waitpid(var.c, NULL, 0);
	while (i)
	{
		waitpid(var.id[i], NULL, 0);
		i--;
	}
	ft_fre(str);
}
