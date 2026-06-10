/*
 * File: 300A.c
 * Author: vididvidid 
 * Created: 2026-06-10 19:02:54
 */

#include <stdio.h>
#include <limits.h>
int main()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    int ng = 0, ps = 0, zo = -1; 
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
        if (arr[i] < 0) ng = arr[i];
        if (arr[i] == 0) zo = 0;
        if (arr[i] > 0) ps = arr[i];
    }
    int ps2 = INT_MIN;
    if (ps == 0) 
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i] != ng && arr[i] < 0 && ps == 0) 
            {
                ps = arr[i];
            }
            if (arr[i] != ng && arr[i] != ps && ps != 0 && arr[i] < 0)
            {
                ps2 = arr[i];
                break;
            }
        }
    }
    int cn = 1;
    printf("1 %d\n",ng);
    if (ps < 0){
        printf("2 %d %d\n",ps2, ps);
        cn += 2;
    }
    else
    {
        printf("1 %d\n",ps);
        cn += 1;
    }
    int tm = cn;
    printf("%d ",n - cn);
    for (int i = 0; i < n; i++)
    {
       if (arr[i] != ng && arr[i] != ps && arr[i] != ps2)
       {
           printf("%d ",arr[i]);
       }
    }
    printf("\n");
    return 0;

}
