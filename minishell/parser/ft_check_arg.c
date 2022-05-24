/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/24 01:49:48 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int check_str(char *str, int i)
{
	if(str[i] && str[i] != '|'  && str[i] != ' '
		&& str[i] != '\'' && str[i] != '"'  && str[i] != '$'
		&& str[i] != '>' && str[i] != '<')
		return(1);
	else
	{
		if(str[i] == '|' && str[i + 1] == '|')
			return(1);
		else if (str[i] == '|' && str[i - 1] == '|')
			return(1);
		return(0);
	}
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
	if(input[j] == '\'' && input[j + 1] == '\'')
		return 0;
	while(input[++j])
	{
		if(input[j] == '\'')
			break ;
	}
	if(input[j] == '\'')
	{
			i++;
			ft_lstadd_back(node, ft_lstnew(ft_substr(input, i, j - i), WR));
			return(j - i + 1);
	}
	return(-1);
}

int	ft_parser_edit1(t_list **node, char *input, int i, char **env)
{
	int		j;
	int		c;
	int		n;
	int		x;
	char	*str;

	j = i;
	if(input[j] == '"' && input[j + 1] == '"')
		return 0;
	while(input[++j])
	{
		if(input[j] == '"')
			break ;
		if(input[j] == '\\')
			break ;
	}
	if(input[j] == '\\')
		return(-1);
	if(input[j] == '"')
	{
		i++;
		c = i - 1;
		while (++c < j)
		{
			if(input[j] == '\\')
				break ;
			if(input[c] == '$')
				break;
		}
		if(input[j] == '\\')
			return(-1);
		if(input[c] == '$')
		{
			ft_lstadd_back(node, ft_lstnew(ft_substr(input, i, c - i), WR));
			n = c++;
			while(check_str(input, c))
				c++;
			str = get_path(env, ft_substr(input, n + 1, c - (n + 1)));
			ft_lstadd_back(node, ft_lstnew(ft_strdup(str), WR));
			n = c;
			while(c < j)
				c++;
			ft_lstadd_back(node, ft_lstnew(ft_substr(input, n, c - n), WR));
		}
		else
			ft_lstadd_back(node, ft_lstnew(ft_substr(input, i, j - i), WR));
		return(j - i + 1);
	}
	return(printf("double codes not close\n"), -1);
}


int	ft_tokinaizer(struct s_list	**node, char *input, char **env)
{
	int		i;
	int		j;
	char	*str;

	j = 1;
	i = 0 ;
	while(input[i] == ' ')
		i++;
	while(i < ft_strlen(input))
	{
		j = 0;
		if (input[i] == ' ')
		{
			while(input[i] == ' ')
				i++;
			if(!input[i])
				break;
			ft_lstadd_back(node, ft_lstnew(ft_strdup(" "), WS));
			i--;
		}
		else if ((input[i] == '|' && input[i + 1] != '|' && input[i - 1] != '|'))
			ft_lstadd_back(node, ft_lstnew(ft_strdup("|"), PIPE));
		else if (input[i] == '"')
		{
			j = ft_parser_edit1(node, input, i, env);
			if(j == -1)
				return 0;
			i += j + 1;
		}
		else if (input[i] == '\'')
		{
			j = ft_parser_edit(node, input, i);
			if(j == -1)
			{
				printf("single codes not close\n");
				return 0;
			}
			i += j + 1;
		}
		else if (input[i] == '$')
		{
			if(!input[i + 1] ||input[i + 1] == ' ')
				ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WR));
			else
			{
				j = i + 1;
				while(check_str(input, j))
					j++;
				str = get_path(env, ft_substr(input, i + 1, j - (i + 1)));
				ft_lstadd_back(node, ft_lstnew(ft_strdup(str), WR));
				i += (j - i);
			}
		}
		else if (input[i] == '>')
			ft_lstadd_back(node, ft_lstnew(ft_strdup(">"), Oredi));
		else if (input[i] == '<')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("<"), Iredi));
		else
		{
			i--;
			while(check_str(input, ++i))
				j++;
			ft_lstadd_back(node, ft_lstnew(ft_substr(input, i - j, j), WR));
		}
		if(!j)
			i++;
	}
	ft_lstadd_back(node, ft_lstnew(strdup("<-"), END_TOKN));
	return(1);
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
		if(head->data)
			free(head->data);
		free(head);
	}
	*lst = NULL;
}

void	printf_list(t_list *lst)
{
	while (lst)
	{
		printf("%s", lst->data);
		lst = lst->next;
	}
	puts("");
}

int	count_Node(t_list *lst, int tokn)
{
	int		count;

	count = 0;
	while (lst)
	{
		if(lst->tokn == tokn)
			count++;
		lst = lst->next;
	}
	return(count);
}

void	ft_lstdelone(t_list *lst)
{
	free(lst->data);
	free(lst);
}


void deleteNode(t_list **head, int key)
{
      t_list *temp;

      if((*head)->tokn == key)
      {
          temp = *head;
          *head = (*head)->next;
          free(temp);
      }
      else
      {
          t_list *current  = *head;
          while(current->next != NULL)
          {
              if(current->next->tokn == key)
              {
				temp = current->next;
				current->next = current->next->next;
				free(temp);
				break;
              }
              else
                  current = current->next;
          }
      }
}

int ft_check_pip(t_list *node)
{
	t_list *head;

	head = node;
	while (head)
	{
		if(head->tokn == PIPE)
			return(1);
		head = head->next;
	}
	return(0);
}

void	ft_pip(t_list *node, char **env)
{
	t_list *head;
	char	*str;
	char	**s;

	str = ft_strdup("");
	head = node->next;
	while (head->tokn != END_TOKN)
	{
		if(head->tokn == PIPE)
			str = ft_strjoin(str, "\t");
		else if(head->tokn == WS)
			str = ft_strjoin(str, "\v");
		else
			str = ft_strjoin(str, head->data);
		head = head->next;
	}
	s = ft_split_2(str, '\t');
	free(str);
	c_pip(s, env, node);
	exit(1);
}

void	ft_ex_com(t_list *node, char **env)
{
	t_list *head;
	char	*str;
	int		pid;

	str = malloc(1);
	str[0] = '\0';
	head = node->next;
	while (head->tokn != END_TOKN)
	{
		if(head->tokn == WS)
			str = ft_strjoin(str, "\v");
		else if (head->data)
			str = ft_strjoin(str, head->data);
		head = head->next;
	}
	if(!str)
	{
		puts("");
		return ;
	}
	// printf("(%s)\n", str);
	pid = fork();
	if(pid == 0)
		ft_child2(str, env, &node);
	waitpid(pid, NULL, 0);
	free(str);
}

void	ft_parser(char *input, char **env)
{
	int		i;
	int		pid;
	t_list	*node;

	i = 0;
	if(input[0] == '\0')
		return;
	node = ft_lstnew(ft_strdup("->"), ST_TOKN);
	if(!ft_tokinaizer(&node, input, env))
		return;
	if(ft_check_pip(node))
	{
		pid = fork();
		if(pid == 0)
		{
			ft_pip(node, env);
			exit(0);
		}
		waitpid(pid, NULL, 0);
	}
	else
		ft_ex_com(node, env);
	// ft_echo(node);
	ft_lstclear(&node);
}