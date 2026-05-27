/*
 * File: 870A.c
 * Author: vididvidid 
 * Created: 2026-05-12 09:53:23
 */

#include <stdio.h>
#include <limits.h>

#define MIN(a,b) (a)<(b)?(a):(b)

int main()
{
    int n, m;
    scanf("%d %d",&n, &m);
    int a1 = INT_MAX, a2 = INT_MAX;
    int arr[10] = {0};
    for (int i = 0; i < n; i++)
    {
        int k;
        scanf("%d",&k);
        arr[k]++;
        a1 = MIN(a1,k);
    }
    for (int i = 0; i < m; i++)
    {
        int k;
        scanf("%d",&k);
        arr[k]++;
        a2 = MIN(a2, k);
    }
    int ans = INT_MAX;
    for (int i = 1; i < 10; i++)
    {
        if (arr[i] == 2) ans = MIN(ans, i);
    }
    if (ans == INT_MAX){
        int num1 = (a1 * 10) + a2;
        int num2 = (a2 * 10) + a1;
        ans = MIN(num1,num2);
    }
    printf("%d\n",ans);
    return 0;
}
