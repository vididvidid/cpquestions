/*
 * File: 816A.c
 * Author: vididvidid 
 * Created: 2026-06-03 11:08:52
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int chk( char *s , char *k )
{
    if (s[0] == k[4] && s[1] == k[3]) return 1;
    return 0;
}

int main()
{
   int h, m, ans = 0;
   scanf("%d:%d",&h, &m);

   while ((h / 10 != m % 10) || (h % 10 != m / 10)) {
       ans++;
       m++;

       if (m == 60) {
           m = 0;
           h++;
       }

       if (h == 24) {
           h = 0;
       }
   }

   printf("%d\n", ans);
   return 0;
}
