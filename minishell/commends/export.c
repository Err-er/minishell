/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:57 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/12 16:33:14 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_dup_env(t_cd *cd)
{
	int i = 0;

	while(cd->my_env[i])
		i++;
	cd->sorted = malloc(sizeof(char *) * (i+1));
	i = 0;
	while(cd->my_env[i])
	{
		cd->sorted[i] = ft_strdup(cd->my_env[i]);
		i++;
	}
	cd->sorted[i] = NULL;
}

void ft_sort_expo(t_cd *cd)
{
	int i = 0;
	int j = 0;
	char *temp;

	ft_dup_env(cd);
	while( cd->sorted[i])
	{
		j = 0;
		while (cd->sorted[j])
		{
			if (cd->sorted[i][0] <= cd->sorted[j][0])
			{
				temp = cd->sorted[i];
				cd->sorted[i] = cd->sorted[j];
				cd->sorted[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	*ft_add_content(char *old,char *new,char *n)
{
	int i = 0;
	char *t;

	t = ft_strdup(n);
	while(old[i] != '=')
		i++;
	i++;
	old = ft_strtrim(old,"\"=");
	t = ft_strjoin(t,"=");
	t = ft_strjoin(t,&old[i]);
	t = ft_strjoin(t,&new[i+1]);
	t = ft_strjoin(t,"\"");
	return(t);
}


void add_this(t_cd *cd, char *s)
{
	int i = 0;
	char *temp;
	char **t;
	char **t1;
	char **t0;
	
	t1 = ft_split_2(s,'+');
	while(cd->my_env[i])
	{
		t = ft_split_2(cd->my_env[i],'=');
		if (t[0] && t1[0] && !ft_strcmp(t[0],t1[0]))
		{
			if (t[1])
				temp = ft_add_content(cd->my_env[i],s,t1[0]);
			else
			{
				temp = ft_strdup(cd->my_env[i]);
				temp = ft_strjoin(temp,"=\"");
				temp = ft_strjoin(temp,&t1[1][1]);
				temp = ft_strjoin(temp,"\"");
			}
			cd->my_env[i] = temp;
			ft_fre(t);
			ft_fre(t1);
			return ;
		}
		ft_fre(t);
		i++;
	}
}

int ft_check_addition(char *s)
{
	int i = 0;
	int x = 0;
	char **t;

	t = ft_split_2(s,'=');
	if (!t)
		return(0);
	while(t[0][i])
	{
		if(t[0][i] == '+')
			x++;
		i++;
	}
	if (x != 1 || (x >= 1 && !t[1]) || t[0][ft_strlen(t[0])-1] != '+')
		return(0);
	return(1);
}

void	ft_print_export(t_cd *cd)
{
	int i = 0;

	while(cd->sorted[i])
	{
		printf("declare -x %s\n",cd->sorted[i]);
		i++;
	}
}

char *ft_cpoy_content(char *s, char *f)
{
	int i = 0;
	char *t;

	f = ft_strtrim(f,"+");
	t = ft_strdup(f);
	while(s[i] != '=')
		i++;
	if (!s[i])
		return(s);
	i++;
	t = ft_strjoin(t,"=\"");
	t = ft_strjoin(t,&s[i]);
	t = ft_strjoin(t,"\"");
	return(t);
}

void	export_this(t_cd *cd, char *s)
{
	char **new_env;
	char **t;
	int i= 0;

	while(cd->my_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while(cd->my_env[i])
	{
		new_env[i] = ft_strdup(cd->my_env[i]);
		i++;
	}
	t = ft_split_2(s,'=');
	if (t[1] && t[0])
		new_env[i] = ft_cpoy_content(s,t[0]);
	else
	{
		if (ft_strchr(s,'=') && t[0])
		{
			new_env[i] = ft_strdup(t[0]);
			new_env[i] = ft_strjoin(new_env[i],"=\"");
			new_env[i] = ft_strjoin(new_env[i],"\"");
			printf("[%s]\n",new_env[i]);
		}
		else
			new_env[i] = ft_strdup(s);
	}
	i++;
	new_env[i] = NULL;
	free(cd->my_env);
	cd->my_env = new_env;
}


void	replace_this(t_cd *cd, char *s)
{
	int i = 0;
	char *temp;
	char **t;
	char **t1;
	
	t1 = ft_split_2(s,'=');
	while(cd->my_env[i])
	{
		t = ft_split_2(cd->my_env[i],'=');
		if (t[0] && t1[0] && !ft_strcmp(t[0],t1[0]))
		{
			if (t1[1])
			{
				temp = ft_cpoy_content(s,t1[0]);
				cd->my_env[i] = temp;
			}
			else
			{
				if (ft_strchr(s,'='))
				{
					cd->my_env[i] = ft_strdup(t[0]);
					cd->my_env[i] = ft_strjoin(cd->my_env[i],"=\"");
					cd->my_env[i] = ft_strjoin(cd->my_env[i],"\"");
				}
			}
			ft_fre(t);
			ft_fre(t1);
			return ;
		}
		ft_fre(t);
		i++;
	}
}

int check_exist(char *s,char **env)
{
	int i = 0;
	char **t;
	char **t1;
	
	t1 = ft_split_2(s,'=');
	t1[0]= ft_strtrim(t1[0],"+");
	while(env[i])
	{
		t = ft_split_2(env[i],'=');
		if (t[0] && t1[0] && !ft_strcmp(t[0],t1[0]))
		{
			ft_fre(t);
			ft_fre(t1);
			return(1);
		}
		ft_fre(t);
		i++;
	}
	ft_fre(t1);
	return(0);
}

int check_char(char c)
{
	if ((c < 48 && c!=43) || (c >= 58 && c != 61 && c < 65) || (c >= 91 && c <=94) || c == 96 || c > 122)
		return(0);
	return(1);
}

int	check_valid(char *s,char **env)
{
	int i = 0;
	int x = 0;
	char *temp;
	char **t;
	

	if (!ft_strcmp(s,"="))
	{
		ds = 1;
		printf("minishell: export: `%s': not a valid identifier\n",s);
		return(0);
	}
	while(env[i])
	{
		if (!ft_strcmp(s, env[i]))
			return(0);
		i++;
	}
	t = ft_split_2(s,'=');
	if (!t)
		return(0);
	i = 0;
	while(t && t[0][i])
	{
		if (!check_char(t[0][i]))
		{
			ds = 1;
			printf("minishell: export: `%s': not a valid identifier\n",s);
			return(0);
		}
		i++;
	}
	i = 0;
	t = ft_split_2(s,'=');
	while(t[0][i])
	{
		if(t[0][i] == '+')
			x++;
		i++;
	}
	if (x > 1 || (x == 1 && !t[1]) || (t[0][ft_strlen(t[0])-1] != '+' && x == 1))
	{
		ds = 1;
		printf("minishell: export: `%s': not a valid identifier\n",s);
		return(0);
	}
	ft_fre(t);
	return(1);
}

void	ft_exprot(t_list **node, t_cd *cd)
{
	t_list *head;
	char *temp;

	head = *node;
	head = head->next;
	ft_sort_expo(cd);

	while(1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break  ;
	}
	if (head->next->tokn == END_TOKN || head->next->tokn == ST_TOKN || head->next->tokn == PIPE)
	{
		ds = 1;
		ft_print_export(cd);
		return ;
	}
	else if (head->next->tokn == OREDI || head->next->tokn == IREDI || head->next->tokn == OUTPUT_H || head->next->tokn == INPUT_H)
	{
		ds = 1;
		ft_print_export(cd);
		return ;
	}
	else
	{
		while(head && (head->next->tokn != END_TOKN || head->next->tokn != ST_TOKN))
		{
			while(head->next->tokn == WS && head->next->tokn != END_TOKN)
				head = head->next;
			while(head->next->tokn == NUL && head->next->tokn != END_TOKN)
				head = head->next;
			if (!head->next->data || head->next->tokn == NUL || (head->tokn == NUL && head->next->tokn == END_TOKN))
			{
				ds = 1;
				printf("minishell: export: `': not a valid identifier\n");
				return ;
			}
			else
			{
				temp = ft_strdup(head->next->data);
				temp = ft_strtrim(temp," ");
				while(head->next->next->tokn == WR || head->next->next->tokn == NUL)
				{
					if(head->next->next->tokn == WR )
					{
						head = head->next;
						temp = ft_strjoin(temp,head->next->data);
					}
					else
						head = head->next;
				}
				if (check_valid(temp,cd->my_env))
				{	
					if (ft_check_addition(temp) && check_exist(temp,cd->my_env))
						add_this(cd, temp);
					else if (!check_exist(temp,cd->my_env ) && head->next->tokn != WS)
						export_this(cd, temp);
					else if (check_exist(temp,cd->my_env) && head->next->tokn != WS)
						replace_this(cd, temp);
				}
				free(temp); 
			}
			if(head->next)
				head = head->next;
		}
	}
}
