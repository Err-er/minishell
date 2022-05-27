#include "minishell.h"
char	*ft_strchrr(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	while (i <= strlen(str))
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (0);
}
char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	char	*s;

	s = 0;
	if (s1 != 0 && set != 0)
	{
		start = 0;
		end = strlen(s1);
		while (s1[start] && ft_strchrr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strchrr(set, s1[end - 1]) && end > start)
			end--;
		s = (char *)malloc(sizeof(char) * (end - start + 1));
		if (!s)
			return (NULL);
		ft_strlcpy(s, &s1[start], end - start + 1);
	}
	return (s);
}

int main()
{
	char *s;

	s = "dfgd    sdf    sdf   sdf s  sdf    sdf s   ";
	printf("(%s)\n",ft_strtrim(s," "));
}