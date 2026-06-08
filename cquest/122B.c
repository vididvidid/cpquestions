/*
 * File: 122B.c
 * Author: vididvidid 
 * Created: 2026-06-08 15:22:22
 */

#include <stdio.h>
#include <string.h>

int main()
{
    int four = 0, seven = 0;
    char s[51];
    scanf("%s",s);
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '4') four++;
        if (s[i] == '7') seven++;
    }

    if (four == 0 && seven == 0)
    {
        printf("-1\n");
    }
    else if (four >= seven)
    {
        printf("4\n");
    }
    else
    {
        printf("7\n");
    }
    return 0;
}
