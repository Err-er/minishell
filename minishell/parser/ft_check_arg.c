/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/15 16:19:09 by asabbar          ###   ########.fr       */
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
		&& str[i] != '>' && str[i] != '<')
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

int	ft_parser_edit(t_list **node, char *input, int i)
{
	int		j;
	int		n;

	j = i;
	if (input[j] == '\'' && input[j + 1] == '\'')
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup(""), NUL)), 0);
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
	return (printf("single quotes not closed\n"), -1);
}
/**********************************/

int	ft_parser_edit1_utils(t_list **node, char *input, t_data *var, char **env)
{
	var->str = ft_substr(input, var->i, var->j - var->i);
	var->x = var->i;
	if (ft_strchr(var->str, '$'))
	{
		var->c = var->i - 1;
		while (++var->c < var->j)
		{
			if (input[var->c] == '$')
			{
				if (var->c - var->x)
					ft_lstadd_back(node, ft_lstnew(ft_substr(input,
								var->x, var->c - var->x), WR));
				var->c += ft_expand(node, input, env, var->c);
				var->x = var->c;
				var->c--;
			}
		}
		if (var->j - var->x)
			ft_lstadd_back(node,
				ft_lstnew(ft_substr(input, var->x, var->j - var->x), WR));
		free(var->str);
	}
	else
		ft_lstadd_back(node, ft_lstnew(var->str, WR));
	return (var->j - var->i + 1);
}

int	ft_parser_edit1(t_list **node, char *input, int i, char **env)
{
	t_data	var;
	char	*str;

	var.j = i;
	var.i = i;
	if (input[var.j] == '"' && input[var.j + 1] == '"')
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup(""), NUL)), 0);
	while (input[++var.j])
	{
		if (input[var.j] == '"')
			break ;
	}
	if (input[var.j] == '"')
	{
		var.i++;
		return (ft_parser_edit1_utils(node, input, &var, env));
	}
	return (printf("double quotes not closed\n"), -1);
}

/**********************************/

int	ft_isalpha(char c)
{
	if (c < 65 || c > 122 || (c < 97 && c > 90))
	{
		if (c != '_')
			return (0);
	}
	return (1);
}
/*********/

int ft_expand_utils(t_list **node, char *input, char **env, int i)
{
	int		j;
	char	*str;
	char	*s;

	j = i + 1;
	while (ft_isalpha(input[j]) || ft_isdigit(input[j]))
	{
		if (ft_isdigit(input[j]) && (i + 1) == j)
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

int ft_expand(t_list **node, char *input, char **env, int i)
{
	int		j;
	char	*str;
	char	*s;

	j = 0;
	if (!input[i + 1] || input[i + 1] == ' ' || input[i + 1] == '$')
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WR)), 2);
	else if (input[i + 1] == '?')
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup(ft_itoa(ds)), WR)), 2);
	else if (!ft_isalpha(input[i + 1]) && !ft_isdigit(input[i + 1]))
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WR)), 1);
	else
		return (ft_expand_utils(node, input, env, i));
}

/***-----*****/

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
/********************S******************/
void ft_pip_utils_1(t_list **head, char **str)
{
	if ((*head)->tokn == PIPE)
	{
		(*str) = ft_strjoin((*str), "\t");
		(*head) = (*head)->next;
	}
	if ((*head)->tokn == WS)
	{
		(*str) = ft_strjoin((*str), "\v");
		(*head) = (*head)->next;
	}
	if ((*head)->tokn == NUL)
	{
		(*str) = ft_strjoin((*str), "\v");
		(*str) = ft_strjoin_nf((*str), ft_strdup(""));
		(*head) = (*head)->next;
	}
	if ((*head)->tokn == WR)
	{
		(*str) = ft_strjoin((*str), (*head)->data);
		(*head) = (*head)->next;
	}
}

void ft_pip_utils_2(t_list **head)
{
	if ((*head)->tokn == OREDI)
	{
		(*head) = (*head)->next;
		while ((*head)->tokn == WS)
			(*head) = (*head)->next;
		while ((*head)->tokn == WR && (*head)->tokn != END_TOKN)
			(*head) = (*head)->next;
	}
	if ((*head)->tokn == OUTPUT_H)
	{
		(*head) = (*head)->next;
		while ((*head)->tokn == WS && (*head)->tokn != END_TOKN)
			(*head) = (*head)->next;
		while ((*head)->tokn == WR && (*head)->tokn != END_TOKN)
			(*head) = (*head)->next;
	}
	if ((*head)->tokn == INPUT_H)
	{
		(*head) = (*head)->next;
		while ((*head)->tokn == WS && (*head)->tokn != END_TOKN)
			(*head) = (*head)->next;
	}
}

char	*ft_pip_utils(t_list *head, char *str)
{
	head = head->next;
	while (head)
	{
		ft_pip_utils_1(&head, &str);
		ft_pip_utils_2(&head);
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

int	 ft_pip(t_list *node, t_cd *cd)
{
	t_list	*head;
	char	*str;
	char	**s;

	str = ft_strdup("");
	str = ft_pip_utils(node, str);
	str = ft_strjoin(str, "\v");
	s = ft_split_2(str, '\t');
	free(str);
	return (c_pip(s, cd, node));
}
/********************N******************/
/*********************************************************************/

int	ft_dup_ex(char *cmds, t_cd *cd, t_vars var, int *end)
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
		return (dup2(var.fd[0], var.x[0]), close(var.fd[0]), 1);
	if (var.fd[1])
		return (dup2(var.fd[1], var.x[1]), close(var.fd[1]), 1);
	return (1);
}

int	ft_ex_cmd(char *cmd, t_cd *cd, t_vars var)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(var.node), 0);
	else if (!ft_strcmp(cmd, "export"))
		return (ft_exprot(&var.node, cd), 0);
	else if (!ft_strcmp(cmd, "exit"))
		return (0);
	else if (!ft_strcmp(cmd, "unset"))
		return (ft_unset(&var.node, cd), 0);
	else if (!ft_strcmp(cmd, "pwd"))
		return (ft_getcwd(cd), 0);
	else if (!ft_strcmp(cmd, "env"))
		return (ft_print_env(cd->my_env), 0);
	else if (!ft_strcmp(cmd, "minishell"))
		return (increase_shelvl(cd), 0);
	return (1);
}

void	ft_ex(char *cmds, t_cd *cd, t_vars var)
{
	char	*pat;
	char	**cmd;
	int		c;
	int		end[2];

	cmd = ft_split_2(cmds, '\v');
	ft_dup_ex(cmds, cd, var, end);
	if (!ft_ex_cmd(cmd[0], cd, var))
		exit(0);
	pat = ft_path(cd->my_env, cmds);
	if (access(cmd[0], X_OK) == 0)
		pat = cmds;
	free(var.value);
	if (execve(pat, cmd, cd->my_env) == -1)
	{
		perror("Error ");
		exit (126);
	}
}

int	ft_ex_oredi(t_list **head, t_vars	*var)
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
	if (var->fd[1] == -1 || !var->file_n[0])
		return (0);
	free(var->file_n);
	var->x[1] = 1;
	return (1);
}

int	ft_ex_output_h(t_list **head, t_vars	*var)
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
	var->fd[1] = open(var->file_n, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (var->fd[1] == -1 || !var->file_n[0])
		return (0);
	free(var->file_n);
	var->x[1] = 1;
	return (1);
}

int	ft_ex_input_h(t_list **head, t_vars	*var)
{
	char	*p;

	var->value = ft_strdup("");
	(*head) = (*head)->next;
	while ((*head)->tokn == WS && (*head)->tokn != END_TOKN)
		(*head) = (*head)->next;
	while (1)
	{
		p = readline("> ");
		if (!ft_strcmp2(p, (*head)->data))
		{
			free(p);
			break ;
		}
		p = ft_strjoin(p, "\n");
		var->value = ft_strjoin(var->value, p);
		free(p);
	}
	return (1);
}

int	ft_ex_iredi(t_list **head, t_vars	*var)
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
	if ((var->fd[0] == -1 || !var->file_n) && (*head)->tokn != 16)
		return (0);
	free(var->file_n);
	var->x[0] = 0;
	return (1);
}

int	ft_ex_com_utils1(t_list **head, t_cd *cd, t_vars *var)
{
	if ((*head)->tokn == OREDI)
	{
		if (!ft_ex_oredi(head, var))
			return (0);
	}
	else if ((*head)->tokn == OUTPUT_H)
	{
		if (!ft_ex_output_h(head, var))
			return (0);
	}
	else if ((*head)->tokn == INPUT_H)
		ft_ex_input_h(head, var);
	else if ((*head)->tokn == IREDI)
	{
		if (!ft_ex_iredi(head, var))
			return (0);
	}
	else
		(*head) = (*head)->next;
	return (1);
}

void	skip_nul(t_list **head, int i)
{
	while ((*head)->tokn == NUL && (*head)->next->tokn == NUL)
		(*head) = (*head)->next;
	if ((*head)->tokn == NUL && i == 0 && (*head)->next->tokn == 0)
		(*head) = (*head)->next;
}

char	*mini_utils(t_list **head, char *str)
{
	skip_nul(head, 1);
	if ((*head)->next->tokn == WS || (*head)->next->tokn == 0)
		str = ft_strjoin(str, " ");
	(*head) = (*head)->next;
	return (str);
}

char	*ft_ex_com_utils(t_list *head, t_cd *cd, t_vars	*var, char *str)
{
	while (head)
	{
		if (head->tokn == WS)
		{
			str = ft_strjoin(str, "\v");
			head = head->next;
		}
		else if (head->tokn == NUL)
			str = mini_utils(&head, str);
		else if (head->tokn == WR)
		{
			str = ft_strjoin(str, head->data);
			head = head->next;
			skip_nul(&head, 0);
		}
		else if (!ft_ex_com_utils1(&head, cd, var))
			return (free(str), free(var->file_n), perror("Error"), NULL);
	}
	if (!str[0])
		return (free(str), NULL);
	return (str);
}

void	ft_ex_com_utils2(t_list *node, t_cd *cd, t_vars	var, char *str)
{
	int		ex;

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

int	ft_ex_com(t_list *node, t_cd *cd)
{
	char	*str;
	char	**cmd;
	t_vars	var;

	var.fd[0] = 0;
	str = ft_strdup("");
	var.value = NULL;
	var.c = 0;
	str = ft_ex_com_utils(node->next, cd, &var, str);
	if (!str)
		return (free(str), free(var.value), 0);
	cmd = ft_split_2(str, '\v');
	if (!cmd[0] || !cmd[0][0])
		return (ft_fre(cmd), free(str), free(var.value), 0);
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(&node, cd);
	else
		ft_ex_com_utils2(node, cd, var, str);
	return (free(str), free(var.value), ft_fre(cmd), 1);
}
/*********************************************************************/

void	ft_ex_sc_utils(t_list *node, t_cd *cd, char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		ft_cd(&node, cd);
	else if (!ft_strcmp(cmd, "echo"))
		ds = 0;
	else if (!ft_strcmp(cmd, "export"))
		ft_exprot(&node, cd);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(&node, cd);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_getcwd(cd);
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(&node);
	else if (!ft_strcmp(cmd, "env"))
		ft_print_env(cd->my_env);
	else if (!ft_strcmp(cmd, "minishell"))
		increase_shelvl(cd);
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
	ft_ex_sc_utils(node, cd, cmd[0]);
	free(str);
	ft_fre(cmd);
}

/*********************************************************************/

char	*ft_sc_utils(t_list *node)
{
	char	*str;

	str = ft_strdup("");
	node = node->next;
	while (node->tokn != END_TOKN)
	{
		if (node->tokn == WS)
			str = ft_strjoin(str, "\v");
		else if (node->tokn == OREDI || node->tokn == IREDI
			|| node->tokn == INPUT_H || node->tokn == OUTPUT_H)
			return (free(str), NULL);
		else if (node->data)
			str = ft_strjoin(str, node->data);
		node = node->next;
	}
	if (!str[0])
		return (NULL);
	return (str);
}

int	ft_sc(t_list *node, t_cd *cd)
{
	char	*str;
	char	**cmd;

	str = ft_sc_utils(node);
	if (!str)
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
	return (ft_fre(cmd), 0);
}
/*********************************************************************/

void	ft_pipe_ex(t_list *node, t_cd *cd)
{
	int		pid;
	int		ex;

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

int	ft_parser(char *input, t_cd *cd)
{
	int		i;
	t_list	*node;

	i = 0;
	if (input[0] == '\0')
		return (1);
	node = ft_lstnew(ft_strdup("->"), ST_TOKN);
	if (!ft_tokinaizer(&node, input, cd->my_env))
		return (0);
	if (!ft_check_syntax(node, input))
		return (ft_lstclear(&node), 0);
	if (node->tokn == node->next->tokn)
		return (ft_lstclear(&node), 0);
	if (ft_check_pip(node, PIPE))
		ft_pipe_ex(node, cd);
	else if (ft_sc(node, cd) == 1)
		ft_ex_sc(node, cd);
	else if (!ft_sc(node, cd))
		ft_ex_com(node, cd);
	ft_lstclear(&node);
	return (1);
}
