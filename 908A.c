/*
 * File: 908A.c
 * Author: vididvidid 
 * Created: 2026-05-06 15:09:40
 */

/*
 * vowel-> even digit (0,2,4,6,8) (a,e,i,o,u)
 */

#include <stdio.h>
#include <string.h>

int main()
{
    char s[51];
    scanf("%s",s);
    int ans = 0;
    for (char *i = s; *i != '\0'; i++)
    {
        if (strchr("aeiou13579",*i)) 
        {
            ans++;
        }
    }

    printf("%d\n",ans);
    return 0;
}
