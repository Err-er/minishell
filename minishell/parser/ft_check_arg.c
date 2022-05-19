/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/19 13:51:51 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		lens;
	char	*copy;

	i = 0;
	if(!src)
		return (NULL);
	while (src[i] != '\0')
		i++;
	lens = i;
	copy = (char *)malloc(lens + 1);
	if (copy == NULL)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
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

int check_str(char *str, int i)
{
	if(str[i] && str[i] != '|' && str[i] != '&' && str[i] != ' '
		&& str[i] != '\'' && str[i] != '"'  && str[i] != '$'
		&& str[i] != '(' && str[i] != ')' && str[i] != '>' && str[i] != '<')
		return(1);
	else
	{
		if(str[i] == '&' && str[i + 1] != '&')
			return(1);
		else
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
	}

	
	if(input[j] == '"')
	{
		i++;
		c = i - 1;
		while (++c < j)
		{
			if(input[c] == '$')
				break;
		}
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
	return(-1);
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
		else if (input[i] == '&' && input[i + 1] == '&')
		{
			ft_lstadd_back(node, ft_lstnew(ft_strdup("&&"), AND));
			i++;
		}
		else if (input[i] == '|' && input[i + 1] == '|')
		{
			ft_lstadd_back(node, ft_lstnew(ft_strdup("||"), OR));
			i++;
		}
		else if (input[i] == '|')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("|"), PIP));
		else if (input[i] == '*')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("*"), ET));
		else if (input[i] == '"')
		{
			j = ft_parser_edit1(node, input, i, env);
			if(j == -1)
			{
				printf("double codes not close\n");
				return 0;
			}
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
		else if (input[i] == '(')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("("), Arch));
		else if (input[i] == ')')
			ft_lstadd_back(node, ft_lstnew(ft_strdup(")"), EArch));
		else if (input[i] == '$')
		{
			j = i + 1;
			while(check_str(input, j))
				j++;
			str = get_path(env, ft_substr(input, i + 1, j - (i + 1)));
			ft_lstadd_back(node, ft_lstnew(ft_strdup(str), WR));
			i += (j - i);
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
	ft_lstadd_back(node, ft_lstnew(strdup("<-"), EN_TOKN));
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

void	ft_parser(char *input, char **env)
{
	int		i;
	int		j;
	t_list	*node;
	

	j = 1;
	i = 0;
	node = ft_lstnew(ft_strdup("->"), ST_TOKN);
	if(!ft_tokinaizer(&node, input, env))
		return;
	ft_echo(node);
	// printf_list(node);
	ft_lstclear(&node);
}