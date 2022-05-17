
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <fcntl.h>
char	*min_strdup(char	*str, int len, int s)
{
	int		i;
	int		j;
	char	*word;

	i = s;
	j = 0;
	word = malloc(len * sizeof(char));
	while(j < len && str[i])
	{
		word[j] = str[i];
		i++;
		j++;
	}
	return(word);
}

int main()
{
    printf("%s\n", min_strdup("adscm cd", 4, 6));
}