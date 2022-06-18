/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:16:35 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/18 15:25:01 by asabbar          ###   ########.fr       */
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
# define WR			11
# define WS			13
# define IREDI		15
# define OREDI		16
# define OUTPUT_H	18
# define INPUT_H	17
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

typedef struct s_data
{
	int		i;
	int		j;
	int		c;
	int		x;
	char	*str;
	char	*limiter;
}	t_data;

int			check_str(char *str, int i);
int			ft_parser_edit1(t_list **node, char *input, int i, char **env);
int			ft_parser_edit(t_list **node, char *input, int i);
int			ft_tokinaizer(t_list **node, char *input, char **env);
long double	ft_atoi(const char *str);
int			ft_parser(char *input, t_cd *cd);
char		**ft_split(char *s, char c);
int			words_count(char *s, char c);
void		ft_lstclear(t_list **lst);
void		ft_echo(t_list *node);
char		*get_path(char **str, char *to_find);
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
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew(char *value, int tokn);
void		utils_ex_ds(int ex);
void		skip_nul(t_list **head, int i);
char		*mini_utils(t_list **head, char *str);
int			ft_tok_input_h_ut1(char *input, t_data *var);
int			ft_tok_input_h_ut2(char *input, t_data *var);
void		ft_tok_input_h_ut3(char *input, t_data *var);
int			ft_tok_input_h(t_list **node, char *input, char **env, t_data *var);
int			ft_isdigit(int c);
int			ft_parser_edit1_utils(t_list **node,
				char *input, t_data *var, char **env);
int			ft_expand_utils(t_list **node, char *input, char **env, int i);
void		ft_pip_utils_2(t_list **head);
void		ft_pip_utils_1(t_list **head, char **str);
int			ft_check_pip3(t_list *node, int c, int c2);
void		ft_ex(char *cmds, t_cd *cd, t_vars var);
int			ft_ex_cmd(char *cmd, t_cd *cd, t_vars var);
int			ft_dup_ex(char *cmds, t_cd *cd, t_vars var, int *end);
int			ft_pip(t_list *node, t_cd *cd);
char		*ft_pip_utils(t_list *head, char *str);
int			ft_ex_com_utils1(t_list **head, t_cd *cd, t_vars *var);
int			ft_ex_iredi(t_list **head, t_vars	*var);
int			ft_ex_input_h(t_list **head, t_vars	*var);
int			ft_ex_output_h(t_list **head, t_vars	*var);
int			ft_ex_oredi(t_list **head, t_vars	*var);
t_list		*new_node_export(t_list	*node);
void		ft_ex_com_utils2(t_list *node, t_cd *cd, t_vars	var, char *str);
char		*ft_ex_com_utils(t_list *head, t_cd *cd, t_vars	*var, char *str);
void		skip_nul(t_list **head, int i);
char		*ft_sc_utils(t_list *node);
void		ft_ex_sc(t_list *node, t_cd *cd);
void		ft_ex_sc_utils(t_list *node, t_cd *cd, char *cmd);
int			ft_ex_com(t_list *node, t_cd *cd);
void		ft_ex_export(t_list *head, t_cd *cd, t_vars var);

#endif