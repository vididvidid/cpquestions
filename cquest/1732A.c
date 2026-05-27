/*
 * File: 1732A.c
 * Author: vididvidid 
 * Created: 2026-05-23 12:38:21
 */

/*
 * make the whole array gcd = 1. by replacing an arr[i] by gcd(arr[i],i)
 * and print the minimum cost (n - i + 1)
 *
 * n = 20 and gcd = 10^9 size element
 *
 */

#include <stdio.h>

#define int long long

int gcd (int a, int b)
{
    if (a && b) for (; (a %= b) && (b %= a); );
    return a | b;
}

void solve()
{
    int n;
    scanf("%lld",&n);
    int arr[n];
    int pgcd[n], sgcd[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld",&arr[i]);
        if(!i) pgcd[i] = arr[i];
        if (i)
        {
            pgcd[i] = gcd(arr[i], pgcd[i - 1]);
        }
    }
    sgcd[n-1] = arr[n-1];
    for (int i = n - 2; i >= 0; i--)
    {
        sgcd[i] = gcd(arr[i], sgcd[i+1]);
    }

    /* for (int i = 0; i < n; i++) printf("%lld ",pgcd[i]); */
    /* printf("\n"); */
    /* for (int i = 0; i < n; i++) printf("%lld ",sgcd[i]); */
    /* printf("\n"); */


    if (pgcd[n - 1] == 1)
    {
        printf("0\n");
    }
    else if ( n == 1 && arr[0] != 1 )
    {
        printf("1\n");
    }
    else if ( n == 1 && arr[0] == 1 )
    {
        printf("0\n");
    }
    else 
    {
        int res = 3;
        for (int i = n - 1; i >= 0; i--)
        {
            int val = gcd(arr[i], i+1);
            int ans = val;
            if ((i - 1) >= 0)
                ans = gcd(val, pgcd[i - 1]);
            if ((i + 1) < n)
                ans = gcd(ans, sgcd[i + 1]);
            if (ans == 1)
            {
                if (n - i < res)
                res = n - i;
                break;
            }
        }
        printf("%lld\n",res);
    }
}

int main()
{
    int t;
    scanf("%lld",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
