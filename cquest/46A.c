/*
 * File: 46A.c
 * Author: vididvidid 
 * Created: 2026-04-26 07:29:13
 */

#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int count = n-1,jump = 1,val =1;
    while (count--)
    {
       val += jump++;
       int t;
       if (val%n == 0) t = n;
       else if (val > n ) t = val%n;
       else t = val;
       printf("%d ",t);
    }
    printf("\n");
    return 0;
}
