/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:16:35 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/13 20:28:57 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <fcntl.h>
# include <termios.h>
# include <stdbool.h>
# include <paths.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# define NUL		-1 
# define ST_TOKN	0
# define PIPE		1
# define CD			6
# define SCD		7
# define WR			11
# define WS			13
# define DOL		14
# define IREDI		15
# define OREDI		16
# define INPUT_H	17
# define OUTPUT_H	18
# define LIMITER	21
# define END_TOKN	0

extern int	ds;

typedef struct s_list
{
	int				tokn;
	char			*data;
	struct s_list	*next;
}	t_list;

typedef struct s_cd
{
	char	**my_env;
	int		env_len;
	char	**sorted;
	char	*oldpwd;
	char	*pwd;
	int		shlvl;
}	t_cd;

typedef struct s_vars
{
	int		c;
	int		br;
	int		c2;
	int		fd[2];
	int		x[2];
	char	*file_n;
	char	*value;
	int		st_in;
	int		st_out;
	t_list	*node;
	int		*id;
	int		end[2];
	char	**str;
	int		i;
}	t_vars;

// typedef struct s_data
// {
// 	int		c;
// 	int		br;
// 	int		c2;
// 	int		fd[2];
// 	int		x[2];
// 	char	*file_n;
// 	char	*value;
// 	int		st_in;
// 	int		st_out;
// 	t_list	*node;
// 	int		end[2];
// }	t_data;

long double	ft_atoi(const char *str);
int			ft_parser(char *input, t_cd *cd);
char		**ft_split(char *s, char c);
int			words_count(char *s, char c);
void		ft_lstclear(t_list **lst);
void		ft_echo(t_list *node);
char		*get_path(char **str, char *to_find);
int			ft_parser_edit1(t_list **node, char *input, int i, char **env);
int			ft_strncmp(char *str1, char *str2, int n);
char		**ft_split_2(char *s, char c);
char		**ft_split(char *s, char c);
int			c_pip(char **str, t_cd *cd, t_list *node);
void		ft_free(char **p, int a);
char		*ft_path(char **env, char *cd);
void		ft_child2(char *cmds, t_cd *cd, t_vars *var);
void		printf_list(t_list *lst);
void		ft_cd(t_list **node, t_cd *cd);
void		ft_ex(char *cmds, t_cd *cd, t_vars var);
void		ft_exprot(t_list **node, t_cd *cd);
void		ft_unset(t_list **node, t_cd *cd);
void		ft_fre(char **cmd);
char		*ft_strjoin_nf(char *s1, char *s2);
char		*ft_substr(char *s, int start, int len);
int			ft_check_pip(t_list *node, int c);
void		ft_putstr_fd(char *s, int fd);
int			ft_check_pip2(t_list *node, int c);
void		ft_getcwd(t_cd *cd);
int			ft_isalpha(char c);
void		ft_print_env(char **env);
void		unset_this(t_cd *cd, char *s);
void		export_this(t_cd *cd, char *s);
int			get_global(int i);
int			ft_is_last(t_list *node, int c, int c2, int end);
int			ft_strcmp2(char *str1, char *str2);
int			ft_expand(t_list **node, char *input, char **env, int i);
int			ft_check_syntax(t_list *node, char *input);
void		ft_exit(t_list **node);
void		increase_shelvl(t_cd *cd);
void		replace_this(t_cd *cd, char *s);
int			ft_cheak_is_expand(char **env, char *cd);

#endif