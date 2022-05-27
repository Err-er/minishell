#include "minishell.h"


static int i = 0;


int main()
{
    printf("i   : %d\n", i);
    int j = fork();

    if(j == 0)
    {
        i+=1;
        exit(1);
    }
    waitpid(j,NULL, 0);
    printf("i   : %d\n", i);

}