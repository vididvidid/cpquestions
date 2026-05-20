/*
 * File: 1796A.c
 * Author: vididvidid 
 * Created: 2026-04-23 02:30:47
 */

/*
 * 3    5   6   9   10  12  15  18  20  21  24  25  27  30
 * F    B   F   F   B   F   FB  F   B   F   F   B   F   FB
 *
 * FBF
 * BFF
 * FFB
 * BFB
 *
 * Q. find if the substring is the part of the string or not.. 
 * string is to be created by following condtion..
 * for every number divisible by 3 append F
 * for every number divisible by 5 append B
 * for every number divisible by both 3 and 5 append F and then B
 *
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 101
char s[MAXLEN];

void solve()
{
   int count = 0;
   for (int i = 1; i < MAXLEN; i++)
   {
        if (i % 3 == 0)
        {
            s[count++] = 'F';
        }
        if (i % 5 == 0)
        {
            s[count++] = 'B';
        }
   }
   s[count] = '\0';

   int n;
   scanf("%d",&n);
   char k[n];
   scanf("%s",k);
   int flag = 0;
   for (int i = 0; i <= MAXLEN; i++)
   {
      int cn = 0;
      int t = i;
      for (int j = 0; j < n; j++)
      {
         if (s[t++] == k[j]){
            cn++;
         }
      }
      if (cn == n) {
         flag = 1;
         break;
      }
   }
   if (flag)
   {
      printf("YES\n");
   } else
   {
      printf("NO\n");
   }
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
