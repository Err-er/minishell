/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/26 21:50:37 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	get_in(char **env, t_cd *cd)
{
	char	*tmp;
	char	b[1024];

	cd->pwd = ft_strdup("PWD=");
	cd->pwd = ft_strjoin(cd->pwd, getcwd(b, 1024));
	if (get_path(env, "SHLVL"))
	{
		tmp = ft_strtrim(get_path(cd->my_env, "SHLVL"), "\"");
		cd->shlvl = ft_atoi(tmp);
		free(tmp);
	}
	else
		cd->shlvl = 0;
}

void	ft_new_env(char **env, t_cd *cd)
{
	int		i;

	i = 0;
	get_in(env, cd);
	if (!env[0])
	{
		cd->my_env = NULL;
		export_this(cd, cd->pwd);
	}
	else if (env && *env)
	{
		while (env[i])
			i++;
		cd->my_env = malloc(sizeof(char *) * i + 1);
		i = -1;
		while (env[++i])
			cd->my_env[i] = ft_strdup(env[i]);
		cd->my_env[i] = NULL;
		replace_this(cd, cd->pwd);
		if (get_path(cd->my_env, "OLDPWD"))
			unset_this(cd, "OLDPWD");
	}
	increase_shelvl(cd);
	export_this(cd, "OLDPWD");
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
