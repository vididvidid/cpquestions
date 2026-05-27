/*
 * File: 1228A.c
 * Author: vididvidid 
 * Created: 2026-05-03 11:16:26
 */

#include <stdio.h>

#define int unsigned long long

signed main()
{
    int l,r;
    scanf("%llu %llu",&l, &r);
    int exit = 0;
    for (int i = l; i <= r; i++)
    {
        int arr[10] = {0};
        int temp = i,flag = 0;
        while (temp > 0)
        {
            int t = temp%10;
            if (arr[t]++)
            {
                flag = 1;
                break;
            }
            temp/=10;
        }
        if (!flag)
        {
            printf("%llu\n",i);
            exit = 1;
            break;
        }
    }
    if (!exit)
         printf("-1\n");
    return 0;
}
