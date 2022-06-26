/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:16:35 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/26 13:14:36 by asabbar          ###   ########.fr       */
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
# define MINI		"minishell"
# define HERE_D		"./parser/here_doc"
# define MINIS		"./minishell"

extern int	g_ds;

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

typedef struct s_mini
{
	char		*p2;
	char		*p;
	int			pid;
	int			fd_h;
}	t_mini;

int				ft_ex_output_h(t_list **head, t_vars *var);
void			remove_ctlc(void);
int				ft_ex_input_h(t_list **head, t_vars *var);
int				check_str(char *str, int i);
int				ft_parser_edit1(t_list **node, char *input, int i, char **env);
int				ft_parser_edit(t_list **node, char *input, int i);
int				ft_tokinaizer(t_list **node, char *input, char **env);
long long		ft_atoi(const char *str);
int				ft_parser(char *input, t_cd *cd);
char			**ft_split(char *s, char c);
int				words_count(char *s, char c);
void			ft_lstclear(t_list **lst);
void			ft_echo(t_list *node);
char			*get_path(char **str, char *to_find);
int				ft_strncmp(char *str1, char *str2, int n);
char			**ft_split_2(char *s, char c);
char			**ft_split(char *s, char c);
int				c_pip(char **str, t_cd *cd, t_list *node);
void			ft_free(char **p, int a);
char			*ft_path(char **env, char *cd);
void			ft_child2(char *cmds, t_cd *cd, t_vars *var);
void			printf_list(t_list *lst);
void			ft_cd(t_list **node, t_cd *cd);
void			ft_ex(char *cmds, t_cd *cd, t_vars var);
void			ft_export(t_list **node, t_cd *cd);
void			ft_unset(t_list **node, t_cd *cd);
char			*ft_substr(char *s, int start, int len);
char			*ft_substr2(char *s, int start, int len);
int				ft_check_pip(t_list *node, int c);
void			ft_putstr_fd(char *s, int fd);
int				ft_check_pip2(t_list *node, int c);
void			ft_getcwd(t_cd *cd);
int				ft_isalpha(char c);
void			ft_print_env(char **env);
void			unset_this(t_cd *cd, char *s);
void			export_this(t_cd *cd, char *s);
int				get_global(int i);
int				ft_is_last(t_list *node, int c, int c2, int end);
int				ft_strcmp2(char *str1, char *str2);
int				ft_expand(t_list **node, char *input, char **env, int i);
int				ft_check_syntax(char *input);
void			ft_exit(t_list **node);
void			increase_shelvl(t_cd *cd);
void			replace_this(t_cd *cd, char *s);
int				ft_cheak_is_expand(char **env, char *cd);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstnew(char *value, int tokn);
void			utils_ex_ds(int ex);
void			skip_nul(t_list **head, int i);
char			*mini_utils(t_list **head, char *str);
int				ft_tok_input_h_ut1(char *input, t_data *var);
int				ft_tok_input_h_ut2(char *input, t_data *var);
void			ft_tok_input_h_ut3(char *input, t_data *var);
int				ft_tok_input_h(t_list **node, char *input, t_data *var);
int				ft_isdigit(int c);
int				ft_parser_edit1_utils(t_list **node,
					char *input, t_data *var, char **env);
int				ft_expand_utils(t_list **node, char *input, char **env, int i);
void			ft_pip_utils_2(t_list **head, char **str);
void			ft_pip_utils_1(t_list **head, char **str);
int				ft_check_pip3(t_list *node, int c, int c2);
void			ft_ex(char *cmds, t_cd *cd, t_vars var);
int				ft_ex_cmd(char *cmd, t_cd *cd, t_vars var);
int				ft_dup_ex(t_vars var, int *end);
void			inisial(t_vars	*var, char **str);
void			ft_check_redi_p(t_vars *var, char *str, t_list *head);
int				ft_iredi_p(t_vars *var, t_list	**head, char *str);
int				ft_inputh_p(t_vars *var, t_list	**head, char *str);
int				ft_check_nul_cm(char *str);
void			ft_change_node(t_list **node);
int				ft_check_red(t_list *node, int fd);
int				ft_check_red2(t_list *node, int fd);
int				ft_oredi_p(t_vars *var, t_list	**head, char *str);
int				ft_outputh_p(t_vars *var, t_list	**head, char *str);
void			dup_chi2(t_vars *var);
void			ft_check_c2(char **cmd, t_cd *cd, t_vars *var);
void			ft_child2(char *cmds, t_cd *cd, t_vars *var);
int				forkpipe(int *end);
int				ft_cheak(int i, char **cmd);
void			ft_check_c1(char **cmds, t_cd *cd, t_vars *var);
void			ft_child1(char *cmd, t_cd *cd, int *end, t_vars *var);
void			dup_chi3(t_vars *var, int *end);
void			ft_check_c3(char **cmds, t_cd *cd, t_vars *var);
void			ft_child3(char *cmd, t_cd *cd, int *end, t_vars *var);
void			ft_fre(char **cmd);
void			print_error_p(char **cmd);
void			ft_f(char **p, char **cmd);
char			*ft_path(char **env, char *cd);
void			dup_chi1(t_vars *var, int *end);
char			*ft_sc_utils(t_list *node);
int				ft_pip(t_list *node, t_cd *cd);
void			ft_ex_sc(t_list *node, t_cd *cd);
int				ft_ex_com(t_list *node, t_cd *cd);
int				ft_ex_com_utils1(t_list **head, t_vars *var);
void			ft_ex_com_utils2(t_list *node, t_cd *cd, t_vars	var, char *str);
char			*ft_ex_com_utils(t_list *head, t_vars	*var, char *str);
t_list			*new_node_export(t_list	*node);
void			run_minishell(t_cd	*cd);
void			ft_new_env(char **env, t_cd *cd);
void			ft_env(t_list **node, t_cd *cd);
int				get_global2(int i);
int				get_global3(int i);
struct termios	get_term(struct termios term, int i);
void			ft_echo_utils(t_list *node);
void			ft_echo_flag(t_list *node);
void			ft_skip_redi(t_list **node, int i);
int				skip_flags(t_list *node, int j);
void			ft_dup_env(t_cd *cd);
void			ft_sort_expo(t_cd *cd);
int				ft_check_addition(char *s);
int				check_exist(char *s, char **env);
void			ft_print_export(t_cd *cd);
int				check_valid(char *s, char **env);
void			add_this(t_cd *cd, char *s);
int				get_pwd(char **env);
void			ft_getcwd(t_cd *cd);
int				get_prev_directory(char *s);
void			print_err(char *s, int er);
int				check_per(char *s);
int				treat_home(t_cd *cd);
void			save_oldpwd(t_cd *cd);
int				treat_minus(t_cd *cd);
int				treat_home(t_cd *cd);
void			save_oldpwd(t_cd *cd);
int				treat_minus(t_cd *cd);
int				treat_prev(t_cd *cd);
void			treat_pnt(t_cd *cd);

#endif