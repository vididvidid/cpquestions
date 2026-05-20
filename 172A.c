/*
 * File: 172A.c
 * Author: vididvidid 
 * Created: 2026-04-26 09:20:52
 */

#include <stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    char s[t][21];
    int arr[20] = {0};
    scanf("%s",s[0]);
    int cnt = 0;
    for (char *i = s[0]; *i != '\0'; i++) arr[cnt++]++;
    for (int i = 1; i < t; i++)
        scanf("%s",s[i]);
    for (int i = 1; i < t; i++)
    {
        for (int j = 0; j < cnt; j++)
        {
            if (s[i][j] == s[0][j]) arr[j]++;
        }
    }

    /* for (int i = 0; i< 20; i++) printf("%d ",arr[i]); */
    /* printf("\n"); */
    int ans = 0;
    for (int i = 0; i< 20; i++) 
    {
        if (arr[i] == t) ans++;
        if (arr[i] != t) break;
    }
    printf("%d\n",ans);
    return 0;
    
}
