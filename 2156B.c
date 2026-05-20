/*
 * File: 2156B.c
 * Author: vididvidid 
 * Created: 2026-05-15 02:53:23
 */

/*
 * clock with B and A and based on B and A perform operation over it until the
 * number becomes 0.. and print the seconds..
 *
 */
#include <stdio.h>

#define int long long 

int flour(float x)
{
    int i = (int)x;
    return i - (i > x);
}

void solve()
{
    int n, q;
    scanf("%lld %lld",&n, &q);
    char s[n];
    scanf("%s",s);
    int a = 0, b = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'A') a++;
    }
    int flaga = 0;
    if (a == n) 
    {
        flaga = 1;
    }

    while (q--)
    {
        int c;
        scanf("%lld",&c);

        int cyc = 0, sec = 0;
        
        if (flaga)
        {
            printf("%lld\n",c);
            continue;
        }
        while (c > 0)
        {
            if (cyc >= n) cyc %= n;
           
            if (s[cyc] == 'A') c--;
            else c = flour((float)c/2.0); 
            
            sec++;
            if (c == 0) break;


            cyc++;
        }

        printf("%lld\n",sec);
    }
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
