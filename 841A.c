/*
 * File: 841A.c
 * Author: vididvidid 
 * Created: 2026-05-12 12:27:47
 */

#include <stdio.h>

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int arr[26] = {0};
    for (int i = 0; i < n; i++)
    {
        char s;
        scanf(" %c",&s);
        arr[s-'a']++;
    }        

    int flag = 0;
    for (int i = 0; i < 26; i++)
    {
        if (arr[i] > k)
         {
            flag = 1;
            break;
        }
    }

    if (flag)
    {
        printf("NO\n");
    }
    else
    {
        printf("YES\n");
    }
    return 0;
}
