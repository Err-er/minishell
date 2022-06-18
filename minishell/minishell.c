/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/18 16:08:49 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	ds = 0;

static char	*mover(char *s1, char *s2, char *s)
{
	int		a;
	int		i;

	a = ft_strlen(s1);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			s[i] = s1[i];
			i++;
		}
	}
	i = 0;
	while (s2[i])
	{
		s[a] = s2[i];
		a++;
		i++;
	}
	s[a] = '\0';
	return (s);
}


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

char	*ft_read(char *rest, int fd)
{
	int		i;
	char	*s;

	s = malloc(1 + 1);
	if (!s)
		return (NULL);
	i = 1;
	while (i && !ft_strchre(rest, '\n'))
	{
		i = read (fd, s, 1);
		if (i == -1)
		{
			free(s);
			return (NULL);
		}
		s[i] = '\0';
		rest = ft_strjoin(rest, s);
	}
	free(s);
	return (rest);
}

char	*ft_line(char *rest)
{
	int		i;
	char	*line;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] != '\n' && rest[i])
		i++;
	if (ft_strchre(rest, '\n'))
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (rest[i] != '\n' && rest[i])
	{
		line[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_rest(char *rest)
{
	int		i;
	int		x;
	char	*newrest;
	int		lnrest;

	i = 0;
	while (rest[i] != '\0' && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	i++;
	x = 0;
	lnrest = ft_strlen(&rest[i]);
	newrest = malloc(lnrest + 1);
	if (!newrest)
		return (NULL);
	while (rest[i])
		newrest[x++] = rest[i++];
	newrest[x] = '\0';
	free(rest);
	return (newrest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0)
		return (NULL);
	rest = ft_read(rest, fd);
	if (!rest)
		return (NULL);
	line = ft_line(rest);
	rest = get_next_rest(rest);
	return (line);
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
		free(input);
	}
}
int	add_hist(int fd_his)
{
	char	*input;

	fd_his = open(HISTORY_COM, O_CREAT | O_RDWR, O_APPEND, 0666);
	input = get_next_line(fd_his);
	while (input)
	{
		input = ft_strtrim2(input, "\n");
		add_history(input);
		free(input);
		input = get_next_line(fd_his);
	}
	free(input);
	return (fd_his);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_cd	*cd;
	int		fd_his;

	(void)av;
	signal(SIGINT, &handle_sigs);
	signal(SIGQUIT, &handle_sigs);
	rl_catch_signals = 0;
	if (ac != 1)
		return (printf("error in argm\n"), 0);
	cd = malloc(sizeof(t_cd));
	ft_new_env(env, cd);
	ds = 0;
	fd_his = add_hist(fd_his);
	run_minishell(cd, fd_his);
	write(1, "\033[1A\033[14Cexit\n", 15);
	ft_fre(cd->my_env);
	free(cd->pwd);
	free(cd);
	return (0);
}
