/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/11 09:55:15 by zait-sli         ###   ########.fr       */
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
		return (ft_lstadd_back(node, ft_lstnew(NULL, NUL)), 0);
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
	int		x;
	char	*str;

	j = i;
	if (input[j] == '"' && input[j + 1] == '"')
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup(""), NUL)), 0);
	while (input[++j])
	{
		if (input[j] == '"')
			break ;
	}
	if (input[j] == '"')
	{
		i++;
		str = ft_substr(input, i, j - i);
		x = i;
		if (ft_strchr(str, '$'))
		{
			c = i - 1;
			while (++c < j)
			{
				if (input[c] == '$')
				{
					if (c - x)
						ft_lstadd_back(node,
							ft_lstnew(ft_substr(input, x, c - x), WR));
					c += ft_expand(node, input, env, c);
					x = c;
				}
			}
			if (j - x)
				ft_lstadd_back(node, ft_lstnew(ft_substr(input, x, j - x), WR));
			free(str);
		}
		else
			ft_lstadd_back(node, ft_lstnew(str, WR));
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

int ft_expand(t_list **node, char *input, char **env, int i)
{
	int		j = 0;
	char	*str;
	char	*s;

	if (!input[i + 1] || input[i + 1] == ' ' || input[i + 1] == '$')
		return(ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WR)), 2);
	else if (input[i + 1] == '?')
		return(ft_lstadd_back(node, ft_lstnew(ft_strdup(ft_itoa(ds)), WR)), 2);
	else if (!ft_isalpha(input[i + 1]) && !ft_isdigit(input[i + 1]))
		return(ft_lstadd_back(node, ft_lstnew(ft_strdup(""), WR)), 2);
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
		s = ft_substr(input, i + 1, j - (i + 1));
		str = get_path(env, s);
		free(s);
		str = ft_strtrim(str, "\"");
		if (str)
			ft_lstadd_back(node, ft_lstnew(str, WR));
		return (j - i);
	}
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
			i += ft_expand(node, input, env, i);
			j = 2;
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			i += 1;
			ft_lstadd_back(node, ft_lstnew(ft_strdup(">>"), OUTPUT_H));
		}
		else if (input[i] == '>')
			ft_lstadd_back(node, ft_lstnew(ft_strdup(">"), OREDI));
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			ft_lstadd_back(node, ft_lstnew(ft_strdup("<<"), INPUT_H));
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
							free(str);
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
							free(str);
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
					free(str);
				}
			}
			ft_lstadd_back(node, ft_lstnew(limiter, LIMITER));
			j = 5;
		}
		else if (input[i] == '<')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("<"), IREDI));
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

int	ft_check_pip3(t_list *node, int c, int c2)
{
	t_list	*head;

	head = node;
	while (head && head->tokn != c2 && head->tokn != PIPE)
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

int	ft_is_last(t_list *node, int c, int c2, int end)
{
	t_list	*head;
	int		nb;

	nb = 1;
	head = node;
	if (head->next)
		head = head->next;
	while (head->tokn != end)
	{
		if (head->tokn == c)
			nb = 1;
		else if (head->tokn == c2)
			nb = 0;
		head = head->next;
		if (!head)
			break ;
	}
	return (nb);
}

int	 ft_pip(t_list *node, t_cd *cd)
{
	t_list	*head;
	char	*str;
	char	**s;

	str = ft_strdup("");
	head = node->next;
	while (head)
	{
		if (head->tokn == PIPE)
		{
			str = ft_strjoin(str, "\t");
			head = head->next;
		}
		else if (head->tokn == WS)
		{
			str = ft_strjoin(str, "\v");
			head = head->next;
		}
		else if (head->tokn == OREDI)
		{
			head = head->next;
			if (head->tokn == WS)
				head = head->next;
			while (head->tokn == WR && head->tokn != END_TOKN)
				head = head->next;
		}
		else if (head->tokn == OUTPUT_H)
		{
			head = head->next;
			if (head->tokn == WS && head->tokn != END_TOKN)
				head = head->next;
			while (head->tokn == WR && head->tokn != END_TOKN)
				head = head->next;
		}
		else if (head->tokn == INPUT_H)
		{
			head = head->next;
			while (head->tokn == WS && head->tokn != END_TOKN)
				head = head->next;
		}
		else if (head->tokn == IREDI)
		{
			head = head->next;
			if (head->tokn == WS)
				head = head->next;
			while (head->tokn == WR && head->tokn != END_TOKN)
				head = head->next;
		}
		else if (head->tokn == NUL)
		{
			str = ft_strjoin(str, "\v");
			str = ft_strjoin_nf(str, ft_strdup(""));
			head = head->next;
		}
		else if (head->tokn == WR)
		{
			str = ft_strjoin(str, head->data);
			head = head->next;
		}
		else
			head = head->next;
	}
	str = ft_strjoin(str, "\v");
	s = ft_split_2(str, '\t');
	free(str);
	int ex = c_pip(s, cd, node);
	return (ex);
}

void	ft_ex(char *cmds, t_cd *cd, t_vars var)
{
	char	*pat;
	char	**cmd;
	int		end[2];
	int		c;

	cmd = ft_split_2(cmds, ' ');
	if (!ft_cheak_is_expand(cd->my_env, cmds))
	{
		ft_fre(cmd);
		cmd = ft_split_2(cmds, '\v');
	}
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
	{
		dup2(var.fd[1], var.x[1]);
		close(var.fd[1]);
	}
	if (!ft_strcmp(cmd[0], "echo"))
	{
		ft_echo(var.node);
		exit(0);
	}
	else if (!ft_strcmp(cmd[0], "export"))
	{
		ft_exprot(&var.node, cd);
		exit(0);
	}
	else if (!ft_strcmp(cmd[0], "exit"))
	{
		exit(0);
	}
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		ft_unset(&var.node, cd);
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
	else if (!ft_strcmp(cmd[0], "minishell"))
	{
		increase_shelvl(cd);
	}
	pat = ft_path(cd->my_env, cmds);
	if (access(cmd[0], X_OK) == 0)
		pat = cmd[0];
	free(cmd);
	free(var.value);
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
	int		ex;
	t_vars	var;
	char	*p;

	var.fd[1] = dup(1);
	var.fd[0] = dup(0);
	str = ft_strdup("");
	var.value = NULL;
	head = node->next;
	var.c = 0;
	while (head)
	{
		if (head->tokn == WS)
		{
			str = ft_strjoin(str, "\v");
			head = head->next;
		}
		else if (head->tokn == OREDI)
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
			var.fd[1] = open(var.file_n, O_CREAT | O_RDWR | O_TRUNC, 0666);
			if (var.fd[1] == -1)
			{
				perror("Error");
				free(var.file_n);
				return ;
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
				var.file_n = ft_strjoin(var.file_n, head->data);
				head = head->next;
			}
			var.fd[1] = open(var.file_n, O_CREAT | O_WRONLY | O_APPEND, 0777);
			if (var.fd[1] == -1)
			{
				perror("Error");
				free(var.file_n);
				return ;
			}
			free(var.file_n);
			var.x[1] = 1;
		}
		else if (head->tokn == INPUT_H)
		{
			var.value = NULL;
			head = head->next;
			while (head->tokn == WS && head->tokn != END_TOKN)
				head = head->next;
			while (1)
			{
				p = readline("> ");
				if (!ft_strcmp2(p, head->data))
				{
					free(p);
					break ;
				}
				p = ft_strjoin(p, "\n");
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
			if ((var.fd[0] == -1 || !var.file_n) && head->tokn != 16)
			{
				perror("Error");
				free(var.file_n);
				return ;
			}
			free(var.file_n);
			var.x[0] = 0;
		}
		else if (head->tokn == NUL)
		{
			str = ft_strjoin(str, ft_strdup(" "));
			head = head->next;
		}
		else if (head->tokn == WR)
		{
			str = ft_strjoin(str, head->data);
			head = head->next;
		}
		else
			head = head->next;
	}
	if (!str[0])
	{
		free(var.value);
		free(str);
		return ;
	}
	cmd = ft_split_2(str, '\v');
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(&node, cd);
	else
	{
		ft_fre(cmd);
		var.node = node;
		get_global(1);
		var.c2 = fork();
		if (var.c2 == 0)
			ft_ex(str, cd, var);
		waitpid(var.c2, &ex, 0);
		if (WIFEXITED(ex))
		{
			if (ex == 65280)
				ds = 255;
			else
				ds = ex % 255;
		}
		else if (WIFSIGNALED(ex))
			ds = ex + 128;
	}
	free(var.value);
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
	else if (!ft_strcmp(cmd[0], "echo"))
		ds = 0;
	else if (!ft_strcmp(cmd[0], "export"))
		ft_exprot(&node, cd);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(&node, cd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_getcwd(cd);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(&node);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_print_env(cd->my_env);
	else if (!ft_strcmp(cmd[0], "minishell"))
		increase_shelvl(cd);
	free(str);
	ft_fre(cmd);
}

int	ft_sc(t_list *node, t_cd *cd)
{
	t_list	*head;
	char	*str;
	char	**cmd;
	int		c;

	str = ft_strdup("");
	head = node->next;
	c = 0;
	while (head->tokn != END_TOKN)
	{
		if (head->tokn == WS)
			str = ft_strjoin(str, "\v");
		else if (head->tokn == OREDI || head->tokn == IREDI
			|| head->tokn == INPUT_H || head->tokn == OUTPUT_H)
		{
			free(str);
			return (0);
		}
		else if (head->data)
			str = ft_strjoin(str, head->data);
		head = head->next;
	}
	if (!str[0])
		return (0);
	cmd = ft_split_2(str, '\v');
	free(str);
	if (!ft_strcmp(cmd[0], "cd"))
		return (ft_fre(cmd), 1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (ft_fre(cmd), 1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_fre(cmd), 1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (ft_fre(cmd), 1);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_fre(cmd), 1);
	else if (!ft_strcmp(cmd[0], "env"))
		return (ft_fre(cmd), 1);
	ft_fre(cmd);
	return (0);
}

void	ft_parser(char *input, t_cd *cd)
{
	int		i;
	int		pid;
	int		ex;
	t_list	*node;

	i = 0;
	if (input[0] == '\0')
		return ;
	node = ft_lstnew(ft_strdup("->"), ST_TOKN);
	if (!ft_tokinaizer(&node, input, cd->my_env))
		return ;
	if (!ft_check_syntax(node, input))
	{
		ft_lstclear(&node);
		return ;
	}
	if (node->tokn == node->next->tokn)
	{
		ft_lstclear(&node);
		return ;
	}
	if (ft_check_pip(node, PIPE))
	{
		get_global(1);
		pid = fork();
		if (pid == 0)
		{
			ex = ft_pip(node, cd);
			if (WIFEXITED(ex))
			{
				if (ex == 65280)
					ds = 255;
				else
					ds = ex % 255;
			}
			else if (WIFSIGNALED(ex))
				ds = ex + 128;
			exit(ds);
		}
		waitpid(pid, &ex, 0);
		if (WIFEXITED(ex))
		{
			if (ex == 65280)
				ds = 255;
			else
				ds = ex % 255;
		}
		else if (WIFSIGNALED(ex))
			ds = ex + 128;
	}
	else if (ft_sc(node, cd) == 1)
		ft_ex_sc(node, cd);
	else if (!ft_sc(node, cd))
		ft_ex_com(node, cd);
	ft_lstclear(&node);
}
