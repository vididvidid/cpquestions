/*
 * File: 855A.c
 * Author: vididvidid 
 * Created: 2026-04-28 13:36:11
 */

/*
 * print if the string apperaed before in the sequence or not
 *
 * at x this string is there..
 * s[arr[x]][string]
 * how you check..
 */

#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d",&n);
    char s[n][101];
    for (int i = 0; i < n; i++) strncpy(s[i],"0",101);
    for (int i = 0; i < n; i++)
    {
        char k[101];
        scanf("%s",k);
        int flag = 0;
        for (int j = 0; j < i; j++)
        {
            if (!strcmp(s[j],k))
            {
                printf("YES\n");
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            strncpy(s[i],k,101);
            printf("NO\n");
        }
    }
    return 0;
}
