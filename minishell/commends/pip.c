/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:22:23 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/26 16:02:53 by asabbar          ###   ########.fr       */
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
void	ft_child1(char *cmd, t_cd *cd, int *end, t_list *node, int fd, int x)
{
	char	*pat;
	char	**cmds;

	pat = ft_path(cd->my_env, cmd);
	cmds = ft_split_2(cmd, '\v');
	if(fd)
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
	// if(!ft_strcmp(cmd, "cd"))
	// {
	// 	ft_cd(node,cd);
	// 	exit(0);
	// }
	else if (execve(pat, cmds, cd->my_env) == -1)
	{
		// printf("error in ft_child1\n");
		perror("Error");
		exit (1);
	}
}

void	ft_child3(char *cmd, t_cd *cd, int *end, t_list *node, int fd, int x)
{
	char	*pat;
	char	**cmds;
	int		c;
	int		nb;
	t_list *head = node;

	pat = ft_path(cd->my_env, cmd);
    cmds = ft_split_2(cmd, '\v');
	c = 0;
	while (head && head->tokn != PIPE)
	{
		if(head->tokn == NB)
		{
			nb = ft_atoi(head->data);
			if(nb == -1)
				c = 0;
			else
				c++;
		}
		else if(head->tokn == Oredi)
		{
			head = head->next;
			fd = open(head->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
			if(!c)
				x = 1;
			else
				x = nb;
		}
		else if(head->tokn == Iredi)
		{
			head = head->next;
			fd = open(head->data, O_RDONLY);
			if(!c)
				x = 0;
			else
				x = nb;
		}
		head = head->next;
	}
	if(fd)
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
	// if(!ft_strcmp(cmd, "cd"))
	// {
	// 	ft_cd(node,env);
	// 	exit(0);
	// }
	if(!ft_strcmp(cmds[0], "echo"))
	{
		puts("here");
		ft_echo(node);
		exit(0);
	}
	else if (execve(pat, cmds, cd->my_env) == -1)
	{
		perror("Error ");
		exit (1);
	}
}

void	ft_child2(char *cmds, t_cd *cd, t_list *node, int fd, int x)
{
	char	*pat;
	char	**cmd;
	char	hh[100];

	pat = ft_path(cd->my_env, cmds);
	cmd = ft_split_2(cmds, '\v');
	if(fd)
	{
		dup2(fd, x);
		close(fd);
	}
	if(!ft_strcmp(cmd[0], "echo"))
	{
		//printf("(%d)\n", ft_strcmp(cmd[0], "echo"));
		ft_echo(node);
		exit(0);
	}
	else if(!ft_strcmp(cmd[0], "pwd"))
	{
		printf("%s\n",getcwd(hh,100));
		exit(0);
		//return ;
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
	while((*node)->tokn != PIPE && (*node))
		(*node) = (*node)->next;
	(*node) = (*node)->next;
		
}

int ft_check_red(t_list *node, int fd)
{
	int nb;
	int c; 
	int i;

	while (node->tokn != PIPE)
	{
		if(node->tokn == NB)
		{
			nb = ft_atoi(node->data);
			if(nb == -1)
				c = 0;
			else
				c++;
		}
		else if(node->tokn == Oredi)
		{
			node = node->next;
			fd = open(node->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
			if(!c)
				i = 1;
			else
				i = nb;
		}
		else if(node->tokn == Iredi)
		{
			node = node->next;
			fd = open(node->data, O_RDONLY);
			if(!c)
				i = 0;
			else
				i = nb;
		}
		node = node->next;
	}
	return (i);
}

int ft_check_red2(t_list *node, int fd)
{
	int nb;

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
	int		st_out;

	i = -1;
	while (str[++i]);
	id = malloc(i * sizeof(int));
	i = -1;
	st_out = dup(1);
	while (str[++i])
	{
		int		c;
		int		nb;
		t_list *head = node;

		c = 0;
		fd = 0;
		while (head && head->tokn != PIPE)
		{
			if(head->tokn == NB)
			{
				nb = ft_atoi(head->data);
				if(nb == -1)
					c = 0;
				else
					c++;
			}
			else if(head->tokn == Oredi)
			{
				head = head->next;
				fd = open(head->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
				if(!c)
					x = 1;
				else
					x = nb;
			}
			else if(head->tokn == Iredi)
			{
				head = head->next;
				fd = open(head->data, O_RDONLY);
				if(!c)
					x = 0;
				else
					x = nb;
			}
			head = head->next;
		}
		id[i] = forkpipe(end);
		if (id[i] == -1)
			exit(1);
		else if (id[i] == 0)
		{
			if (i == 0)
				ft_child1(str[i], cd, end, node, fd, x);
			else if (ft_cheak(i, str) == 2)
				ft_child2(str[i], cd, node, fd, x);
			else if (ft_cheak(i, str) == 3)
				ft_child3(str[i], cd, end, node, fd, x);
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