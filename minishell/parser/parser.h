/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:16:35 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/19 15:22:13 by asabbar          ###   ########.fr       */
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

# define UND		-1
# define ST_TOKN	0	//start
# define PIP		1	//	|  !
# define AND		2	//	&&
# define OR			3	//	||
# define point		5	//	.
# define CD			6	//	"
# define SCD		7	//	'
# define ET			8	//	*
# define Arch		9	//	( 
# define EArch		10	//	)
# define WR			11	//	Word
# define WS			13	//	space ' '
# define DOL		14	//	Dollar $ !
# define Iredi		15	//	< !
# define Oredi		16	//	> ! 
# define EN_TOKN	0	//	End

typedef struct s_list
{
	int				tokn;
	char			*data;
	struct s_list	*next;
}	t_list;

void	ft_parser(char *input, char **env);
char	**ft_split(char *s, char c);
int		words_count(char *s, char c);
void	ft_lstclear(t_list **lst);
void    ft_echo(t_list *node);
char	*get_path(char **str, char *to_find);
int		ft_parser_edit1(t_list **node, char *input, int i, char **env);
int		ft_strncmp(char *str1, char *str2, int n);
#endif