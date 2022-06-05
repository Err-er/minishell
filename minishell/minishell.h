/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:51:33 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/05 16:22:50 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include "./parser/parser.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_strtrim(char *s1, char *set);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strnstr(char *str, char *to_find);
char	*ft_strdup(char *src);
int		ft_strlen(char *s);
int		ft_strlen1(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strchrr(char *str, int c);
int		ft_strlcpy(char *dest, char *src, int size);
char	*ft_itoa(int n);
int		ft_isdigit(int c);
#endif