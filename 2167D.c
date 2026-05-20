/*
 * File: 2167D.c
 * Author: vididvidid 
 * Created: 2026-05-14 05:25:23
 */

#include <stdio.h>
#include <limits.h>
#define MAXLEN 100001
#define MIN(a,b) (a)<(b)?(a):(b)

int prime[MAXLEN] = {0};

long long int getans(long long int mn)
{
    long long int ans = LLONG_MAX;
    if (mn == 1) {
        return 2;
    }
    if (mn == 2) {
        return 3;
    }
    // num is odd and greater than 3 print n-2 
    if (mn%2!=0 && mn>3) {
        /* printf("DEBUG: ODD and val: %lld\n",mn-2); */
        ans = MIN(ans, mn-2);
    }  
    // num is greater than 3 than print n-1
    if (mn > 2) {
        /* printf("DEBUG: >2 and val: %lld\n",mn-1); */
        ans = MIN(ans,mn-1);
        // find the smallest prime..
       int val = INT_MAX;
       for (int i = 2; i < mn; i++)
       {
           if (prime[i] == 0 && mn%i!=0)
           {
               val = i;
               break;
               /* printf("%lld\n",val); */
           }
       }
       ans = MIN(ans, val);
    } 
    // num is prime and greater than 2 print 2
    // num is prime and and x is not divisble by num
    return ans;
}
void solve()
{
    for (int i = 2; i * i < MAXLEN; i++)
    {
        if (prime[i] == 0) {
            for (int j = i * i; j < MAXLEN; j+=i)
            {
                prime[j] = -1;
            }
        }
    }


    int n;
    scanf("%d",&n);
    long long int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld",&arr[i]);
    }
    long long int val = LLONG_MAX;
    for (int i = 0; i < n; i++)
    {
        long long int tval = getans(arr[i]);
        val = MIN(val, tval);
    }
    printf("%lld\n",val);
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
