/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:51:33 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/23 18:30:58 by zait-sli         ###   ########.fr       */
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
char	*ft_strchr(char *str, int c);
int		ft_strlcpy(char *dest, char *src, int size);
char	*ft_itoa(int n);
int		ft_isdigit(int c);
int		ft_check_pipe(char *input);
int		ft_check_input_h(char *input);
int		ft_check_iredi(char *input);
int		ft_check_output_h(char *input);
int		ft_check_oredi(char *input);
void	print_error_syntax(void);
char	*ft_strtrim2(char *s1, char *set);
int		ft_check_nul_cm(char *str);
char	*get_next_line(int fd);
char	*ft_strchre(const char *s, int c);
int		get_global(int i);
void	handle_sigs(int sig);
char	*ft_strchre(const char *s, int c);
void	ft_putstr(char	*c);
int		ft_isprint(int c);

#endif