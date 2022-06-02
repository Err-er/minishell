/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/02 17:52:44 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (s)
	{
		while (s[++i] != '\0')
			write(fd, &s[i], 1);
	}
}

char	*ft_substr(char *s, int start, int len)
{
	int			lenght;
	int			x;
	char		*sub;

	x = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	lenght = ft_strlen(&s[start]);
	if (lenght >= len)
		lenght = len;
	sub = malloc(lenght + 1);
	if (!sub)
		return (NULL);
	while (s[start] && x < len)
		sub[x++] = s[start++];
	sub [x] = '\0';
	return (sub);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	else
		return (1);
}

int	check_str(char *str, int i)
{
	if (str[i] && str[i] != '|' && str[i] != ' '
		&& str[i] != '\'' && str[i] != '"' && str[i] != '$'
		&& str[i] != '>' && str[i] != '<' && str[i] != '/')
		return (1);
	else
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (1);
		else if (str[i] == '|' && str[i - 1] == '|')
			return (1);
		return (0);
	}
	return (0);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	return (ft_lstlast(lst->next));
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (*lst)
	{
		head = *lst;
		head = ft_lstlast(head);
		head -> next = new;
	}
	else
		*lst = new;
}

t_list	*ft_lstnew(char *value, int tokn)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = value;
	new->tokn = tokn;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*head;
	int		c;

	head = lst;
	c = 0;
	while (head)
	{
		c++;
		head = head->next;
	}
	return (c);
}

int	ft_parser_edit(t_list **node, char *input, int i)
{
	int		j;
	int		n;

	j = i;
	if (input[j] == '\'' && input[j + 1] == '\'')
		return (0);
	while (input[++j])
	{
		if (input[j] == '\'')
			break ;
	}
	if (input[j] == '\'')
	{
		i++;
		ft_lstadd_back(node, ft_lstnew(ft_substr(input, i, j - i), WR));
		return (j - i + 1);
	}
	return (-1);
}

int	ft_parser_edit1(t_list **node, char *input, int i, char **env)
{
	int		j;
	int		c;
	int		n;
	int		x;
	char	*str;

	j = i;
	if (input[j] == '"' && input[j + 1] == '"')
		return (ft_lstadd_back(node, ft_lstnew(NULL, WR)), 0);
	while (input[++j])
	{
		if (input[j] == '"')
			break ;
	}
	if (input[j] == '"')
	{
		i++;
		c = i - 1;
		while (++c < j)
		{
			if (input[c] == '$')
				break ;
		}
		if (input[c] == '$')
		{
			if (c - i)
				ft_lstadd_back(node, ft_lstnew(ft_substr(input, i, c - i), WR));
			if (ft_isalpha(input[c]) || ft_isdigit(input[c]))
			{
				ft_lstadd_back(node, ft_lstnew(ft_strdup(""), WR));
				c++;
			}
			if (!input[c + 1] || input[c + 1] == ' ' || input[c + 1] == '$')
			{
				ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WR));
				c++;
			}
			else if (!input[c + 1] || input[c + 1] == '?')
			{
				ft_lstadd_back(node, ft_lstnew(ft_strdup(ft_itoa(ds)), WR));
				c++;
			}
			else
			{
				while (ft_isalpha(input[c]) || ft_isdigit(input[c]))
				{
					if (ft_isdigit(input[c]) && input[c - 1] == '$')
					{
						c++;
						break ;
					}
					c++;
				}
				str = get_path(env, ft_substr(input, n + 1, c - (n + 1)));//free --->  ft_substr(input, n + 1, c - (n + 1))
				str = ft_strtrim(str, "\"");
				if (str)
					ft_lstadd_back(node, ft_lstnew(ft_strdup(str), WR));
			}
			n = c++;
			n = c;
			while (c < j)
				c++;
			if (c - n)
				ft_lstadd_back(node, ft_lstnew(ft_substr(input, n, c - n), WR));
		}
		else
			ft_lstadd_back(node, ft_lstnew(ft_substr(input, i, j - i), WR));
		return (j - i + 1);
	}
	return (printf("double quotes not closed\n"), -1);
}

int	ft_isalpha(char c)
{
	if (c < 65 || c > 122 || (c < 97 && c > 90))
	{
		if (c != '_')
			return (0);
	}
	return (1);
}

int	ft_tokinaizer(struct s_list	**node, char *input, char **env)
{
	int		i;
	int		j;
	char	*str;
	char	*limiter;

	j = 1;
	i = 0 ;
	while (input[i] == ' ')
		i++;
	while (i < ft_strlen(input))
	{
		j = 0;
		if (input[i] == ' ')
		{
			if (input[i + 1] != '|')
			{	
				while (input[i] == ' ')
					i++;
				if (!input[i])
					break ;
				ft_lstadd_back(node, ft_lstnew(ft_strdup(" "), WS));
				i--;
			}
		}
		else if ((input[i] == '|'
				&& input[i + 1] != '|' && input[i - 1] != '|'))
			ft_lstadd_back(node, ft_lstnew(ft_strdup("|"), PIPE));
		else if (input[i] == '"')
		{
			j = ft_parser_edit1(node, input, i, env);
			if (j == -1)
				return (0);
			i += j + 1;
		}
		else if (input[i] == '\'')
		{
			j = ft_parser_edit(node, input, i);
			if (j == -1)
				return (printf("single quotes not closed\n"), 0);
			i += j + 1;
		}
		else if (input[i] == '$')
		{
			if (!input[i + 1] || input[i + 1] == ' ' || input[i + 1] == '$')
			{
				ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WR));
				i++;
			}
			else if (!ft_isalpha(input[j]) || !ft_isdigit(input[j]))
			{
				ft_lstadd_back(node, ft_lstnew(ft_strdup(""), WR));
				i++;
			}
			else if (!input[i + 1] || input[i + 1] == '?')
			{
				ft_lstadd_back(node, ft_lstnew(ft_strdup(ft_itoa(ds)), WR));
				i++;
			}
			else
			{
				j = i + 1;
				while (ft_isalpha(input[j]) || ft_isdigit(input[j]))
				{
					if (ft_isdigit(input[j]))
					{
						j++;
						break ;
					}
					j++;
				}
				str = get_path(env, ft_substr(input, i + 1, j - (i + 1))); // free   ft_substr(input, i + 1, j - (i + 1));
				str = ft_strtrim(str, "\"");
				if (str)
					ft_lstadd_back(node, ft_lstnew(ft_strdup(str), WR));
				i += (j - i);
			}
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			i += 2;
			ft_lstadd_back(node, ft_lstnew(ft_strdup(">>"), output_h));
		}
		else if (input[i] == '>')
			ft_lstadd_back(node, ft_lstnew(ft_strdup(">"), Oredi));
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			limiter = ft_strdup("");
			i += 2;
			ft_lstadd_back(node, ft_lstnew(ft_strdup("<<"), input_h));
			while (input[i] == ' ')
				i++;
			while (input[i] && input[i] != ' ' && input[i] != '<'
				&& input[i] != '>' && input[i] != '|')
			{
				if (input[i] == '"')
				{
					if (input[i] == '"' && input[i + 1] == '"')
					{
						str = ft_strdup("");
						i += 2;
						j = 1;
					}
					else
					{
						i++;
						j = 0;
						while (input[i] && input[i] != '"')
						{
							j++;
							i++;
						}
						if (!input[i])
							return (printf("double quotes not closed\n"), 0);
						else
						{
							str = ft_substr(input, i - j, j);
							limiter = ft_strjoin(limiter, str);
						}
						i++;
					}
				}
				else if (input[i] == '\'')
				{
					if (input[i] == '"' && input[i + 1] == '"')
					{
						str = ft_strdup("");
						i += 2;
						j = 1;
					}
					else
					{
						i++;
						j = 0;
						while (input[i] && input[i] != '\'')
						{
							j++;
							i++;
						}
						if (!input[i])
							return (printf("single quotes not closed\n"), 0);
						else
						{
							str = ft_substr(input, i - j, j);
							limiter = ft_strjoin(limiter, str);
						}
						i++;
					}
				}
				else
				{
					j = 0;
					while (input[i] && input[i] != '\'' && input[i] != '"'
						&& input[i] != ' ' && input[i] != '<'
						&& input[i] != '>' && input[i] != '|')
					{
						j++;
						i++;
					}
					str = ft_substr(input, i - j, j);
					limiter = ft_strjoin(limiter, str);
				}
			}
			ft_lstadd_back(node, ft_lstnew(ft_strdup(limiter), LIMITER));
			free(limiter);
		}
		else if (input[i] == '<')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("<"), Iredi));
		else
		{
			if (input[i] != ' ')
			{
				i--;
				while (check_str(input, ++i) || input[i] == '/')
					j++;
				ft_lstadd_back(node, ft_lstnew(ft_substr(input, i - j, j), WR));
			}
		}
		if (!j)
			i++;
	}
	ft_lstadd_back(node, ft_lstnew(strdup("<-"), END_TOKN));
	return (1);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*head;

	if (!lst)
		return ;
	while (*lst)
	{
		head = *lst;
		*lst = (*lst)->next;
		if (head->data)
			free(head->data);
		free(head);
	}
	*lst = NULL;
}

void	printf_list(t_list *lst)
{
	while (lst)
	{
		printf("(%s - %d)\n", lst->data, lst->tokn);
		lst = lst->next;
	}
	puts("");
}

int	ft_check_pip(t_list *node, int c)
{
	t_list	*head;

	head = node;
	while (head)
	{
		if (head->tokn == c)
			return (1);
		head = head->next;
	}
	return (0);
}

int	ft_check_pip2(t_list *node, int c)
{
	t_list	*head;

	head = node;
	while (head)
	{
		if (head->tokn == PIPE)
			break ;
		if (head->tokn == c)
			return (1);
		head = head->next;
	}
	return (0);
}

void	ft_pip(t_list *node, t_cd *cd)
{
	t_list	*head;
	char	*str;
	char	**s;

	str = ft_strdup("");
	head = node->next;
	while (head->tokn != END_TOKN)
	{
		if (head->tokn == PIPE)
			str = ft_strjoin(str, "\t");
		else if (head->tokn == Oredi)
		{
				head = head->next;
			while (head->tokn == WS && head->tokn != END_TOKN)
				head = head->next;
		}
		else if (head->tokn == output_h)
		{
				head = head->next;
			while (head->tokn == WS && head->tokn != END_TOKN)
				head = head->next;
		}
		else if (head->tokn == input_h)
			head = head->next;
		else if (head->tokn == Iredi)
		{
			head = head->next;
			while (head->tokn == WS && head->tokn != END_TOKN)
				head = head->next;
		}
		else if (head->tokn == WS)
			str = ft_strjoin(str, "\v");
		else
			str = ft_strjoin(str, head->data);
		head = head->next;
	}
	s = ft_split_2(str, '\t');
	free(str);
	c_pip(s, cd, node);
	exit(1);
}

void	ft_ex(char *cmds, t_cd *cd, t_list *node, int *fd, int *i, char *value)
{
	char	*pat;
	char	**cmd;
	int		end[2];

	cmd = ft_split_2(cmds, '\v');
	if (ft_check_pip(node, input_h))
	{
		if (pipe(end) == -1)
			perror("Error");
		ft_putstr_fd(value, end[1]);
		close(end[1]);
		dup2(end[0], 0);
		close(end[0]);
	}
	else
	{
		dup2(fd[0], i[0]);
		close(fd[0]);
	}
	dup2(fd[1], i[1]);
	close(fd[1]);
	if (!ft_strcmp(cmd[0], "echo"))
	{
		ft_echo(node);
		exit(0);
	}
	else if (!ft_strcmp(cmd[0], "export"))
	{
		ft_exprot(&node, cd);
		exit(0);
	}
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		ft_unset(&node, cd);
		exit(0);
	}
	else if (!ft_strcmp(cmd[0], "pwd"))
	{
		ft_getcwd(cd);
		exit(0);
	}
	else if (!ft_strcmp(cmd[0], "env"))
	{
		ft_print_env(cd->my_env);
		exit(0);
	}
	pat = ft_path(cd->my_env, cmds);
	if (access(cmd[0], X_OK) == 0)
		pat = cmd[0];
	if (execve(pat, cmd, cd->my_env) == -1)
	{
		perror("Error ");
		exit (1);
	}
}

void	ft_ex_com(t_list *node, t_cd *cd)
{
	t_list	*head;
	char	*str;
	char	**cmd;
	int		pid;
	int		fd[2];
	int		end[2];
	int		i[2];
	int		c;
	char	*p;
	char	*value;
	char	*file_n;

	str = ft_strdup("");
	value = ft_strdup("");
	head = node->next;
	c = 0;
	while (head)
	{
		if (head->tokn == WS)
			str = ft_strjoin(str, "\v");
		else if (head->tokn == Oredi)
		{
			file_n = ft_strdup("");
			head = head->next;
			if (head->tokn == WS)
				head = head->next;
			while (head->tokn == WR && head->tokn != END_TOKN)
			{
				file_n = ft_strjoin_nf(file_n, head->data);
				head = head->next;
			}
			if (ft_strchr(file_n, '/'))
			{
				printf("minishell: %s: No such file or directory\n", file_n);
				return ;
			}
			fd[1] = open(file_n, O_CREAT | O_RDWR | O_TRUNC, 0666);
			free(file_n);
			i[1] = 1;
		}
		else if (head->tokn == output_h)
		{
			file_n = ft_strdup("");
			head = head->next;
			if (head->tokn == WS && head->tokn != END_TOKN)
				head = head->next;
			while (head->tokn == WR && head->tokn != END_TOKN)
			{
				file_n = ft_strjoin_nf(file_n, head->data);
				head = head->next;
			}
			if (ft_strchr(file_n, '/'))
			{
				printf("minishell: %s: No such file or directory\n", file_n);
				return ;
			}
			fd[1] = open(file_n, O_CREAT | O_WRONLY | O_APPEND, 0777);
			free(file_n);
			i[1] = 1;
		}
		else if (head->tokn == input_h)
		{
			// puts("hhhhhhhhhhhh");
			value = ft_strdup("");
			head = head->next;
			while (head->tokn == WS && head->tokn != END_TOKN)
				head = head->next;
			while (1)
			{
				p = readline("> ");
				if (!ft_strcmp(p, head->data))
					break ;
				p = ft_strjoin_nf(p, "\n");
				value = ft_strjoin(value, p);
				free(p);
			}
		}
		else if (head->tokn == Iredi)
		{
			file_n = ft_strdup("");
			head = head->next;
			if (head->tokn == WS)
				head = head->next;
			while (head->tokn == WR && head->tokn != END_TOKN)
			{
				file_n = ft_strjoin(file_n, head->data);
				head = head->next;
			}
			fd[0] = open(file_n, O_RDONLY);
			if (fd[0] == -1 || !file_n)
			{
				printf("minishell: %s: No such file or directory\n", file_n);
				return ;
			}
			free(file_n);
			i[0] = 0;
		}
		else if (head->tokn == WR)
			str = ft_strjoin(str, head->data);
		head = head->next;
	}
	if (!str[0])
		return ;
	cmd = ft_split_2(str, '\v');
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(&node, cd);
	else
	{
		get_global(1);
		pid = fork();
		if (pid == 0)
			ft_ex(str, cd, node, fd, i, value);
		waitpid(pid, NULL, 0);
	}
	if (!value[0])
		free(value);
	ft_fre(cmd);
	free(str);
}

void	ft_ex_sc(t_list *node, t_cd *cd)
{
	t_list	*head;
	char	*str;
	char	**cmd;
	int		c;

	str = malloc(1);
	str[0] = '\0';
	head = node->next;
	c = 0;
	while (head->tokn != END_TOKN)
	{
		if (head->tokn == WS)
			str = ft_strjoin(str, "\v");
		else if (head->data)
			str = ft_strjoin(str, head->data);
		head = head->next;
	}
	cmd = ft_split_2(str, '\v');
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(&node, cd);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_exprot(&node, cd);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(&node, cd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_getcwd(cd);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_print_env(cd->my_env);
	free(str);
	ft_fre(cmd);
}

int	ft_sc(t_list *node, t_cd *cd)
{
	t_list	*head;
	char	*str;
	char	**cmd;
	int		c;

	str = malloc(1);
	str[0] = '\0';
	head = node->next;
	c = 0;
	while (head->tokn != END_TOKN)
	{
		if (head->tokn == WS)
			str = ft_strjoin(str, "\v");
		else if (head->tokn == Oredi)
			return (0);
		else if (head->tokn == Iredi)
			return (0);
		else if (head->data)
			str = ft_strjoin(str, head->data);
		head = head->next;
	}
	if (!str[0])
		return (0);
	cmd = ft_split_2(str, '\v');
	free(str);
	if (!ft_strcmp(cmd[0], "cd"))
	{
		ft_fre(cmd);
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "export"))
	{
		ft_fre(cmd);
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		ft_fre(cmd);
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "pwd"))
	{
		ft_fre(cmd);
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "env"))
	{
		ft_fre(cmd);
		return (1);
	}
	ft_fre(cmd);
	return (0);
}

void	ft_parser(char *input, t_cd *cd)
{
	int		i;
	int		pid;
	t_list	*node;

	i = 0;
	if (input[0] == '\0')
		return ;
	node = ft_lstnew(ft_strdup("->"), ST_TOKN);
	if (!ft_tokinaizer(&node, input, cd->my_env))
		return ;
	if (node->tokn == node->next->tokn)
	{
		ft_lstclear(&node);
		return ;
	}
	if (ft_check_pip(node, PIPE))
	{
		pid = fork();
		if (pid == 0)
		{
			ft_pip(node, cd);
			exit(0);
		}
		waitpid(pid, NULL, 0);
	}
	else if (ft_sc(node, cd) == 1)
		ft_ex_sc(node, cd);
	else if (!ft_sc(node, cd))
		ft_ex_com(node, cd);
	ft_lstclear(&node);
}
