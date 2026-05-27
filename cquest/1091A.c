/*
 * File: 1091A.c
 * Author: vididvidid 
 * Created: 2026-04-26 06:25:26
 */

#include <stdio.h>

int main()
{
    int a,b,c;
    scanf("%d %d %d",&a, &b,&c);
    int t = a;
    while (t--)
    {
        /* printf("DEBUG: %d %d %d\n",a,b,c); */
        if (a < b && a < c && (a+1 < c)  )
        {
            printf("%d\n",a+(a+1)+(a+2));
            break;
        }
        a--;
    }
    return 0;
}
