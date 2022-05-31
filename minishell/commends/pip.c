/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:22:23 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/31 17:42:22 by asabbar          ###   ########.fr       */
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
    cmd = ft_split_2(cd, ' ');
	if(access(cmd[0], X_OK) == 0)
	{
		ft_fre(cmd);
		ft_fre(p);
        return (cmd[0]);
	}
	if (!cmd[0])
	{
		ft_fre(cmd);
		ft_fre(p);
		exit(0);
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
	printf("minishell : command not found: ");
	printf("%s", cmd[0]);
	printf("\n");
	ft_fre(cmd);
	exit(1);
}
void	ft_child1(char *cmd, t_cd *cd, int *end, t_list *node, int fd, int x, char *value)
{
	char	*pat;
	char	**cmds;
	char	hh[100];

	cmds = ft_split_2(cmd, ' ');
	pat = ft_path(cd->my_env, cmd);
	if (access(cmds[0], X_OK) == 0)
		pat = cmds[0];
	if((ft_check_pip2(node, Oredi) || ft_check_pip2(node, Iredi)) && !ft_check_pip(node, input_h))
	{
		dup2(fd, x);
		close(fd);
	}
	else
	{
		dup2(end[1], 1);
		close(end[0]);
		close(end[1]);
	}
	if(!ft_strcmp(cmds[0], "echo"))
	{
		ft_echo(node);
		exit(0);
	}
	else if(!ft_strcmp(cmds[0], "pwd"))
	{
		printf("%s\n",getcwd(hh,100));
		exit(0);
	}
	if (execve(pat, cmds, cd->my_env) == -1)
	{
		perror("Error");
		exit (1);
	}
}

void	ft_child3(char *cmd, t_cd *cd, int *end, t_list *node, int fd, int x, char *value)
{
	char	*pat;
	char	**cmds;
	int		c;
	char	hh[100];
	t_list *head = node;
	int		p[2];

    cmds = ft_split_2(cmd, ' ');
	pat = ft_path(cd->my_env, cmd);
	if (access(cmds[0], X_OK) == 0)
		pat = cmds[0];
	if(ft_check_pip2(node, Oredi) || ft_check_pip2(node, Iredi))
	{
		dup2(fd, x);
		close(fd);
	}
	else
	{
		dup2(end[1], 1);
		close(end[0]);
		close(end[1]);
	}
	if(!ft_strcmp(cmds[0], "echo"))
	{
		puts("here");
		ft_echo(node);
		exit(0);
	}
	else if(!ft_strcmp(cmds[0], "pwd"))
	{
		printf("%s\n",getcwd(hh,100));
		exit(0);
	}
	if (execve(pat, cmds, cd->my_env) == -1)
	{
		perror("Error ");
		exit (1);
	}
}

void	ft_child2(char *cmds, t_cd *cd, t_list *node, int fd, int x, char *value)
{
	char	*pat;
	char	**cmd;
	char	hh[100];
	int		end[2];

	cmd = ft_split_2(cmds, ' ');
	pat = ft_path(cd->my_env, cmds);
	if (access(cmd[0], X_OK) == 0)
		pat = cmd[0];
	if((ft_check_pip2(node, Oredi) || ft_check_pip2(node, Iredi)) && !ft_check_pip(node, input_h))
	{
		dup2(fd, x);
		close(fd);
	}
	if(!ft_strcmp(cmd[0], "echo"))
	{
		ft_echo(node);
		exit(0);
	}
	else if(!ft_strcmp(cmd[0], "pwd"))
	{
		printf("%s\n",getcwd(hh,100));
		exit(0);
	}
	if (execve(pat, cmd, cd->my_env) == -1)
	{
		perror("Error ");
		exit (1);
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
	while((*node)->tokn != PIPE && (*node))
	{
		if((*node)->next->tokn == END_TOKN)
			break ;
		(*node) = (*node)->next;
	}
	(*node) = (*node)->next;
		
}

int ft_check_red(t_list *node, int fd)
{
	int c; 
	int i;

	while (node->tokn != PIPE)
	{
		 if(node->tokn == Oredi)
		{
			node = node->next;
			fd = open(node->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
				i = 1;
		}
		else if(node->tokn == Iredi)
		{
			node = node->next;
			fd = open(node->data, O_RDONLY);
				i = 0;
		}
		node = node->next;
	}
	return (i);
}

int ft_check_red2(t_list *node, int fd)
{
	while (node->tokn != PIPE && node)
	{
		if(node->tokn == Oredi)
		{
			node = node->next;
			fd = open(node->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
		}
		else if(node->tokn == Iredi)
		{
			node = node->next;
			fd = open(node->data, O_RDONLY);
		}
		node = node->next;
	}
	return (fd);
}

void    c_pip(char **str, t_cd *cd, t_list *node)
{
	int		end[2];
	int		*id;
	int		c;
	int		i;
	int		fd;
	int		x;
	t_list	*head;
	char	*file_n;
	char	*value;
	char	*p;
	int		st_in;

	i = -1;
	file_n = ft_strdup("");
	value = ft_strdup("");
	while (str[++i]);
	id = malloc(i * sizeof(int));
	i = -1;
	st_in = dup(0);
	// printf_list(node);
	while (str[++i])
	{
		c = 0;
		fd = 0;
		head = node;
		while (head && head->tokn != PIPE)
		{
			// printf("data   :   %s\n", head->data);
			if(head->tokn == Oredi)
			{
				file_n = ft_strdup("");
				head = head->next;
				if(head->tokn == WS)
					head = head->next;
				while(head->tokn == WR && head->tokn != END_TOKN)
				{
					file_n = ft_strjoin_nf(file_n, head->data);
					head = head->next;
				}
				if(ft_strchr(file_n, '/'))
				{
					printf("minishell: %s: No such file or directory\n", file_n);
					return ;
				}
				fd = open(file_n, O_CREAT | O_RDWR | O_TRUNC, 0666);
				free(file_n);
				x = 1;
			}
			else if(head->tokn == output_h)
			{
				file_n = ft_strdup("");
				head = head->next;
				if(head->tokn == WS)
					head = head->next;
				while(head->tokn == WR && head->tokn != END_TOKN)
				{
					file_n = ft_strjoin_nf(file_n, head->data);
					head = head->next;
				}
				if(ft_strchr(file_n, '/'))
				{
					printf("minishell: %s: No such file or directory\n", file_n);
					return ;
				}
				fd = open(file_n, O_CREAT | O_WRONLY | O_APPEND, 0777);
				free(file_n);
				x = 1;
			}
			else if(head->tokn == input_h)
			{
				value = ft_strdup("");
				head = head->next;
				while(head->tokn == WS && head->tokn != END_TOKN)
					head = head->next;
				if(pipe(end) == -1)
					perror("Error");
				if(!ft_check_pip(head,input_h))
				{
					dup2(st_in, 0);
					close(st_in);
				}
				while (1)
				{
					p = readline("> ");
					if(!ft_strcmp(p, head->data))
					{
						free(p);
						break;
					}
					p = ft_strjoin_nf(p,"\n");
					value = ft_strjoin(value,p);
					free(p);
				}
			}
			else if(head->tokn == Iredi)
			{
				file_n = ft_strdup("");
				head = head->next;
				if(head->tokn == WS)
					head = head->next;
				while(head->tokn == WR && head->tokn != END_TOKN)
				{
					file_n = ft_strjoin_nf(file_n, head->data);
					head = head->next;
				}
				if(ft_strchr(file_n, '/'))
				{
					printf("minishell: %s: No such file or directory\n", file_n);
					return ;
				}
				fd = open(file_n, O_RDONLY);
				free(file_n);
				x = 0;
			}
			head = head->next;
		}
		if(ft_check_pip2(node, input_h) && value)
		{
			if(pipe(end) == -1)
				perror("Error");
			ft_putstr_fd(value, end[1]);
			close(end[1]);
			dup2(end[0], 0);
			close(end[0]);
		}
		id[i] = forkpipe(end);
		if (id[i] == -1)
			exit(1);
		if (id[i] == 0)
		{
			if (i == 0)
				ft_child1(str[i], cd, end, node, fd, x, value);
			else if (ft_cheak(i, str) == 2)
				ft_child2(str[i], cd, node, fd, x, value);
			else if (ft_cheak(i, str) == 3)
				ft_child3(str[i], cd, end, node, fd, x, value);
		}
		if (i == 0 && !ft_check_pip2(node, input_h))
			c = id[i];
		ft_change_node(&node);
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
