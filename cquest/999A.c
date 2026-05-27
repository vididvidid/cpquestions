/*
 * File: 999A.c
 * Author: vididvidid 
 * Created: 2026-04-26 06:37:00
 */

#include <stdio.h>

int main()
{
    int n, k;
    scanf("%d %d",&n, &k);
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d",&arr[i]);
    int ans = 0;
    int l = 0, r= n-1;
    while (l < n && arr[l]<=k) ans++,l++;
    while (r >= l && arr[r]<=k) ans++,r--;
    printf("%d\n",ans);
    return 0;
}
