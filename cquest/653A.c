/*
 * File: 653A.c
 * Author: vididvidid 
 * Created: 2026-05-13 05:58:51
 */

#include <stdio.h>

#define MIN(a,b) (a)<(b)?(a):(b)

int main()
{
    int n;
    scanf("%d",&n);
    int arr[1001] = {0};
    for (int i = 0; i < n; i++)
    {
        int k;
        scanf("%d",&k);
        arr[k]++;
    }
    int flag1 = 0, flag2 = 0;
    for (int i = 0; i < 999; i++)
    {
        flag1 = 0;
        flag2 = 0;
        if (arr[i] > 0)
        {
            if (arr[i+1] > 0) flag1 = 1;
            if (arr[i+2] > 0) flag2 = 1;
            /* printf("DEBUG: %d:%d | %d:%d | %d:%d\n",i,arr[i],i+1,arr[i+1],i+2,arr[i+2]); */
            if (flag1 && flag2) break;
        }
    }
    if ((flag1 == 1) && (flag2 == 1)) printf("YES\n");
    else printf("NO\n");
    return 0;
}
