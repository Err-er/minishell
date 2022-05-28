#include "./parser/parser.h"

char *ft_new_file(char *txt)
{
    char *new;
    int i = 0;
    int j = 0;
    while(txt[i])
    {
        if(txt[i] ==  '"')
            break ;
        if(txt[i] ==  '\'')
            break ;
    }
    if(txt[i] ==  '"')
    {
        j = i;
        new = ft_substr(txt, i - j, i);
        while(txt[++j])
        {
            if(txt[j] ==  '"')
                break ;
        }
        if(txt[j] ==  '"')
            new = ft_strjoin(new, ft_substr(txt, i + 1, j - (i + 1)));
    }
}
int main()
{
    char *str = strdup("\"achraf\"");
    printf("%s\n", str);
    printf("%s\n", ft_new_file(str));
}