/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:16:35 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/27 17:17:54 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <fcntl.h>

# define UND		-1  // undefined
# define ST_TOKN	0	//	start
# define PIPE		1	//	|  !
# define CD			6	//	"
# define SCD		7	//	'
# define WR			11	//	Word
# define WS			13	//	space ' '
# define DOL		14	//	Dollar $ !
# define Iredi		15	//	< !
# define Oredi		16	//	> ! 
# define input_h	17	//	<< !
# define output_h	18	//	>> ! 
# define file		19	//	file of input or output  {> , < , >> , <<}
# define NB			20	//	number before 3>, ?>
# define LIMITER	21	//	LIMITER of herdoc
# define END_TOKN	0	//	End

typedef struct s_list
{
	int				tokn;
	char			*data;
	struct s_list	*next;
}	t_list;


// typedef struct s_cd
// {
// 	char	**my_env;
// 	int		env_len;
// 	char	**exported;
// 	char	*oldpwd;
// }	t_gl;

typedef struct s_gl
{
	char	**my_env;
	int		env_len;
	char	**exported;
	char	*oldpwd;
}	t_cd;


long long	ft_atoi(const char *str);
void	ft_parser(char *input, t_cd *cd);
char	**ft_split(char *s, char c);
int		words_count(char *s, char c);
void	ft_lstclear(t_list **lst);
void    ft_echo(t_list *node);
char	*get_path(char **str, char *to_find);
int		ft_parser_edit1(t_list **node, char *input, int i, char **env);
int		ft_strncmp(char *str1, char *str2, int n);
char	**ft_split_2(char *s, char c);
char	**ft_split(char *s, char c);
void    c_pip(char **str, t_cd *cd, t_list *node);
void	ft_free(char **p, int a);
char	*ft_path(char **env, char *cd);
void	ft_child2(char *cmds, t_cd *cd, t_list *node, int fd, int x);
void	printf_list(t_list *lst);
void	ft_cd(t_list **node, t_cd *cd);
void	ft_ex(char *cmds, t_cd *cd, t_list *node, int fd, int i);
void	ft_exprot(t_list **node, t_cd *cd);
void	ft_unset(t_list **node, t_cd *cd);
void	ft_fre(char **cmd);
#endif