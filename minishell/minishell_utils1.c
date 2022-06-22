/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/22 17:14:54 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

char	*ft_strchre(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)s);
}

void	ft_new_env(char **env, t_cd *cd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
		i++;
	cd->my_env = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (env[++i])
		cd->my_env[i] = ft_strdup(env[i]);
	cd->my_env[i] = NULL;
	if (get_path(cd->my_env, "OLDPWD"))
		unset_this(cd, "OLDPWD");
	cd->pwd = ft_strdup("PWD=");
	cd->pwd = ft_strjoin(cd->pwd, get_path(cd->my_env, "PWD"));
	tmp = ft_strtrim(get_path(cd->my_env, "SHLVL"), "\"");
	cd->shlvl = ft_atoi(tmp);
	free(tmp);
}

void	handle_sigs(int sig)
{
	struct termios	term;

	term.c_ispeed = 0;
	if (sig == SIGINT && get_global2(-1) != 0 && get_global3(1) == 1)
	{
		get_global3(0);
		term = get_term(term, 0);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		printf("\n");
		exit(1);
	}
	else if (sig == SIGINT && !get_global(15) && get_global2(-1) == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	get_global(int i)
{
	static int	j;

	if (i == 0)
		j = 0;
	else if (i == 1)
		j = 1;
	else
		return (j);
	return (j);
}

int	get_global2(int i)
{
	static int	j;

	if (i != -1)
		j = i;
	return (j);
}
