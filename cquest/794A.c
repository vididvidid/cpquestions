/*
 * File: 794A.c
 * Author: vididvidid 
 * Created: 2026-04-30 18:12:14
 */

#include <stdio.h>

int main()
{
    int a,b,c;
    scanf("%d %d %d",&a, &b, &c);
    int n;
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d",&arr[i]);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > b  && arr[i] < c) ans++;
        
    }
    printf("%d\n",ans);
    return 0;
}
