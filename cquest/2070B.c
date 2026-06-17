/*
 * File: 2070B.c
 * Author: vididvidid 
 * Created: 2026-06-17 22:51:43
 */

#include <stdio.h>

#define int long long

void solve()
{
   int n, x, k;
   scanf("%lld %lld %lld",&n, &x, &k);

   char s[n + 1];
   scanf("%s", s);

   int t1 = -1;
   int curr = x;

   for (int i = 0; i < n; i++)
   {
       if (s[i] == 'L') curr--;
       else curr++;

       if (curr == 0)
       {
           t1 = i + 1;
           break;
       }
   }

   if (t1 == -1 || t1 > k) 
   {
       printf("0\n");
       return;
   }

   int t2 = -1;
   curr = 0;

   for (int i = 0; i < n; i++)
   {
       if (s[i] == 'L') curr--;
       else curr++;

       if (curr == 0)
       {
           t2 = i + 1;
           break;
       }
   }

   if (t2 == -1)
   {
       printf("1\n");
       return;
   }

   int ans = 1 + (k - t1) / t2;
   printf("%lld\n",ans);
}

signed main()
{
    int t;
    scanf("%lld",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
