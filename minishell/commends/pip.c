/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:22:23 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/15 10:49:20 by asabbar          ###   ########.fr       */
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

/********************************************************/
/********************************************************/
/********************************************************/
/********************************************************/

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
	if (!cmd)
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

int	ft_cheak_is_expand(char **env, char *cd)
{
	int		i;
	char	*str;
	char	*str2;
	char	**p;
	char	**cmd;

	str = get_path(env, "PATH");
	p = ft_split(str, ':');
	cmd = ft_split_2(cd, ' ');
	if (access(cmd[0], X_OK) == 0)
		return (ft_fre(p), 1);
	if (!cmd)
		return (ft_fre(cmd), 0);
	i = -1;
	while (p[++i])
	{
		str2 = ft_strjoin(p[i], cmd[0]);
		if (access(str2, X_OK) == 0)
			return (ft_fre(cmd), 1);
		free(str2);
	}
	return (ft_fre(cmd), 0);
}
//********************************ch 3 **********************//
//********************************ch 3 **********************//
//********************************ch 3 **********************//
//********************************ch 3 **********************//
//********************************ch 3 **********************//

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

void	ft_check_c1(char **cmds, t_cd *cd, t_vars *var, char *hh)
{
	if (!ft_strcmp(cmds[0], "export"))
	{
		ft_exprot (&var->node, cd);
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
		printf("%s\n", getcwd(hh, 100));
		exit(0);
	}
}

void	ft_child1(char *cmd, t_cd *cd, int *end, t_vars *var)
{
	char	*pat;
	char	**cmds;
	char	hh[100];

	dup_chi1(var, end);
	cmds = ft_split_2(cmd, '\v');
	ft_check_c1(cmds, cd, var, hh);
	pat = ft_path(cd->my_env, cmd);
	if (access(cmds[0], X_OK) == 0)
		pat = cmds[0];
	if (execve(pat, cmds, cd->my_env) == -1)
	{
		perror("Error");
		exit (127);
	}
}

//********************************ch 3 **********************//
//********************************ch 3 **********************//
//********************************ch 3 **********************//
//********************************ch 3 **********************//
//********************************ch 3 **********************//

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
	if (ft_check_pip2(var->node, OREDI) || ft_check_pip2(var->node, OUTPUT_H))
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

void	ft_check_c3(char **cmds, t_cd *cd, t_vars *var, char *hh)
{
	if (!ft_strcmp(cmds[0], "export"))
	{
		ft_exprot (&var->node, cd);
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
		printf("%s\n", getcwd(hh, 100));
		exit(0);
	}
}

void	ft_child3(char *cmd, t_cd *cd, int *end, t_vars *var)
{
	char	*pat;
	char	**cmds;
	char	hh[100];

	dup_chi3(var, end);
	cmds = ft_split_2(cmd, '\v');
	ft_check_c3(cmds, cd, var, hh);
	pat = ft_path(cd->my_env, cmd);
	if (access(cmds[0], X_OK) == 0)
		pat = cmds[0];
	if (execve(pat, cmds, cd->my_env) == -1)
	{
		perror("Error ");
		exit (127);
	}
}
//********************************ch 2 **********************//
//********************************ch 2 **********************//
//********************************ch 2 **********************//
//********************************ch 2 **********************//
//********************************ch 2 **********************//

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

void	ft_check_c2(char **cmd, t_cd *cd, t_vars *var, char *hh)
{
	if (!ft_strcmp(cmd[0], "export"))
	{
		ft_exprot(&var->node, cd);
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
		printf("%s\n", getcwd(hh, 100));
		exit(0);
	}
}

void	ft_child2(char *cmds, t_cd *cd, t_vars *var)
{
	char	*pat;
	char	**cmd;
	char	hh[100];

	dup_chi2(var);
	cmd = ft_split_2(cmds, '\v');
	ft_check_c2(cmd, cd, var, hh);
	pat = ft_path(cd->my_env, cmds);
	if (access(cmd[0], X_OK) == 0)
		pat = cmd[0];
	if (execve(pat, cmd, cd->my_env) == -1)
	{
		perror("Error ");
		exit (127);
	}
}
/******************************************************/
/******************************************************/
/******************************************************/
/******************************************************/
/******************************************************/

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

void	ft_change_node(t_list **node)
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

int	ft_oredi_p(t_vars *var, t_list	**head, char *str)
{
	var->file_n = ft_strdup("");
	(*head) = (*head)->next;
	if ((*head)->tokn == WS)
		(*head) = (*head)->next;
	while ((*head)->tokn == WR && (*head)->tokn != END_TOKN)
	{
		var->file_n = ft_strjoin(var->file_n, (*head)->data);
		(*head) = (*head)->next;
	}
	var->fd[1] = open(var->file_n, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (var->fd[1] == -1 || !var->file_n)
	{
		perror("Error");
		free(var->file_n);
		var->br = 1;
		return (0);
	}
	if (!ft_strcmp(str, "\v\v")
		|| !ft_strcmp(str, " \v\v") || !ft_strcmp(str, "\v"))
		var->br = 1;
	free(var->file_n);
	var->x[1] = 1;
	return (1);
}

int	ft_outputh_p(t_vars *var, t_list	**head, char *str)
{
	var->file_n = ft_strdup("");
	(*head) = (*head)->next;
	if ((*head)->tokn == WS && (*head)->tokn != END_TOKN)
		(*head) = (*head)->next;
	while ((*head)->tokn == WR && (*head)->tokn != END_TOKN)
	{
		var->file_n = ft_strjoin(var->file_n, (*head)->data);
		(*head) = (*head)->next;
	}
	var->fd[1] = open(var->file_n,
			O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (var->fd[1] == -1 || !var->file_n)
	{
		perror("Error");
		free(var->file_n);
		var->br = 1;
		return (0);
	}
	if (!ft_strcmp(str, "\v\v")
		|| !ft_strcmp(str, " \v\v") || !ft_strcmp(str, "\v"))
		var->br = 1;
	free(var->file_n);
	var->x[1] = 1;
	return (1);
}

int	ft_inputh_p(t_vars *var, t_list	**head, char *str)
{
	char	*p;

	var->value = NULL;
	(*head) = (*head)->next;
	while ((*head)->tokn == WS && (*head)->tokn != END_TOKN)
		(*head) = (*head)->next;
	dup2(var->st_in, 0);
	while (1)
	{
		p = readline("> ");
		if (!ft_strcmp2(p, (*head)->data))
		{
			free(p);
			break ;
		}
		p = ft_strjoin_nf(p, "\n");
		var->value = ft_strjoin(var->value, p);
		free(p);
	}
	if (!ft_strcmp(str, "\v\v")
		|| !ft_strcmp(str, " \v\v") || !ft_strcmp(str, "\v"))
		var->br = 1;
	return (1);
}

int	ft_iredi_p(t_vars *var, t_list	**head, char *str)
{
	var->file_n = ft_strdup("");
	(*head) = (*head)->next;
	if ((*head)->tokn == WS)
		(*head) = (*head)->next;
	while ((*head)->tokn == WR && (*head)->tokn != END_TOKN)
	{
		var->file_n = ft_strjoin(var->file_n, (*head)->data);
		(*head) = (*head)->next;
	}
	var->fd[0] = open(var->file_n, O_RDONLY);
	if (var->fd[0] == -1 || !var->file_n)
	{
		perror("Error");
		var->br = 1;
		free(var->file_n);
		return (0);
	}
	if (!ft_strcmp(str, "\v\v")
		|| !ft_strcmp(str, " \v\v") || !ft_strcmp(str, "\v"))
		var->br = 1;
	free(var->file_n);
	var->x[0] = 0;
	return (1);
}

void	ft_check_redi_p(t_vars *var, char *str, t_list *head)
{
	while (head && head->tokn != PIPE)
	{
		if (head->tokn == OREDI)
		{
			if (!ft_oredi_p(var, &head, str))
				break ;
		}
		else if (head->tokn == OUTPUT_H)
		{
			if (!ft_outputh_p(var, &head, str))
				break ;
		}
		else if (head->tokn == INPUT_H)
		{
			if (!ft_inputh_p(var, &head, str))
				break ;
		}
		else if (head->tokn == IREDI)
		{
			if (!ft_iredi_p(var, &head, str))
				break ;
		}
		else
			head = head->next;
	}
}

void	inisial(t_vars	*var, char **str)
{
	var->br = 0;
	var->c = 0;
	var->c2 = 0;
	var->i = 0;
	var->file_n = ft_strdup("");
	var->value = NULL;
	while (str[var->i])
		var->i++;
	var->id = malloc(var->i * sizeof(int));
	var->i = -1;
	var->st_in = dup(0);
	var->st_out = dup(1);
	var->str = str;
}

void	ft_ex_com_pipe(t_vars *var, t_cd *cd, t_list *node)
{
	if (ft_check_pip2(node, INPUT_H) && var-> value)
	{
		if (pipe(var->end) == -1)
			perror("Error");
		ft_putstr_fd(var->value, var->end[1]);
		close(var->end[1]);
		dup2(var->end[0], 0);
		close(var->end[0]);
	}
	var->id[var->i] = forkpipe(var->end);
	if (var->id[var->i] == -1)
		exit(127);
	if (var->id[var->i] == 0)
	{
		var->node = node;
		if (!var->str[var->i + 1])
			var->c2 = 1;
		if (var->i == 0)
			ft_child1(var->str[var->i], cd, var->end, var);
		else if (ft_cheak(var->i, var->str) == 2)
			ft_child2(var->str[var->i], cd, var);
		else if (ft_cheak(var->i, var->str) == 3)
			ft_child3(var->str[var->i], cd, var->end, var);
	}
}

int	ft_wait_p(t_vars *var)
{
	int	j;
	int	ex;

	j = -1;
	while (++j < var->i)
		waitpid(var->id[j], &ex, 0);
	return (ex);
}

void	ft_dup_p(t_vars *var)
{
	if (var->br)
	{
		if (pipe(var->end) == -1)
			perror("Error");
	}
	if (var->str[var->i + 1])
	{
		dup2(var->end[0], 0);
		close(var->end[0]);
		close(var->end[1]);
	}
	else
	{
		dup2(var->st_in, 0);
		dup2(var->st_out, 1);
		close(var->end[0]);
		close(var->end[1]);
	}
	var->br = 0;
	var->c = 0;
	var->c2 = 0;
}

int	c_pip(char **str, t_cd *cd, t_list *node)
{
	t_vars	var;

	inisial(&var, str);
	while (var.str[++var.i])
	{
		ft_check_redi_p(&var, var.str[var.i], node);
		if (!var.br)
			ft_ex_com_pipe(&var, cd, node);
		ft_dup_p(&var);
		ft_change_node(&node);
	}
	ft_fre(str);
	return (ft_wait_p(&var));
}
