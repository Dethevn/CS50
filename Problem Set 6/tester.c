#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>

int main(void)
{
	char line[] = {'g', 'e', 't', ' ', '/', 's', 'o', 'y', 'k', 'q', '\?' , 'h', 'i', ' ', 'H', 'T', '\0'};
    
    char array[] = "";
    char *rs = strchr(line, 'q');
    int j = 0;
    
    for (char *i = rs; *i != ' '; i++)
    {
        array[j]=*i;
        j++;
    }
    array[j++] = '\0';
    
    char q1[];
    strcpy(q1, strchr(line, ' '));
    
    printf("%s", q1);
    
}
// clang -ggdb3 -O0 -std=c99 -Wall -Werror    tester.c  -lcs50 -lm -o tester

