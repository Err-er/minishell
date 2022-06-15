/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokinaizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:36:41 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/14 18:37:48 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_tokinaizer_sp(va_list **node, char *input, char **env, int *i)
{
	{
		if (input[(*i) + 1] != '|')
		{	
			while (input[i] == ' ')
				i++;
			if (!input[i])
				return ;
			ft_lstadd_back(node, ft_lstnew(ft_strdup(" "), WS));
			i--;
		}
	}
}

int	ft_tokinaizer_sp(va_list **node, char *input, char **env, int i)
{
	char	*limiter;
	char	*str;
	int		j;

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

int	ft_tokinaizer(va_list **node, char *input, char **env)
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
		else if (input[i] == '|')
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
				while (check_str(input, ++i) && input[i] != '|')
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