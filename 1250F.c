/*
 * File: 1250F.c
 * Author: vididvidid 
 * Created: 2026-04-25 12:53:23
 */

#include <stdio.h>
#define int unsigned long long
signed  main()
{
    int n;
    scanf("%llu",&n);
    int fact1 = 1 , fact2 = 0;
    for (int i = 1; i * i <= n ; i++)
    {
        if (n % i == 0){
            fact1 = i;
            fact2 = n/i;
        }
    }
    /* for (int i = 0; i < count; i++) */
    /*     printf("%d ",arr[i]); */
    /* printf("%d %d\n",arr[count-1],arr[count-2]); */
    int area = (2 * fact1) + (2* fact2);
    printf("%llu\n",area);
    return 0;
}
