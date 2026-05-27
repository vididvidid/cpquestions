/*
 * File: 988A.c
 * Author: vididvidid 
 * Created: 2026-04-29 10:23:39
 */

#include <stdio.h>

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int arr[101] = {0};
    for (int i = 0; i < n; i++)
    {
        int t; 
        scanf("%d",&t);
        arr[t] = i+1;
    }
    int srr[k];
    int count = 0;
    for (int i = 0; i < 101; i++)
    {
        if (count == k) break;
        if (arr[i] > 0) 
        {
            srr[count++] = arr[i];
        }
    }
    if (count == k)
    {
        printf("YES\n");
        for (int i = 0; i < k; i++) printf("%d ",srr[i]);
        printf("\n");
    }
    else {
        printf("NO\n");
    }
}
