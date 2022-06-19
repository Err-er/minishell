/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/19 16:56:52 by asabbar          ###   ########.fr       */
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
	if (sig == SIGINT && !get_global(15))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		printf("\n");
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

void	run_minishell(t_cd	*cd, int fd_his)
{
	char	*input;

	while (1)
	{
		get_global(0);
		input = readline("➜ minishell $ ");
		if (!input)
			break ;
		ft_parser(input, cd);
		if (input[0])
		{
			ft_putstr_fd(input, fd_his);
			ft_putstr_fd("\n", fd_his);
			add_history(input);
		}
		system("leaks minishell");
		free(input);
	}
}
