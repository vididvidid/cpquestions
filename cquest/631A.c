/*
 * File: 631A.c
 * Author: vididvidid 
 * Created: 2026-05-13 06:34:44
 */

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) (a)>(b)?(a):(b)

int main()
{
    int n;
    scanf("%d",&n);
    long long arr[n],brr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld",&arr[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%lld",&brr[i]);
    }

    long long m1 = LONG_MIN, m2 = LONG_MIN;
    for (int i = 0; i < n; i++)
    {
        long long t = arr[i];
        m1 = MAX(m1, t);
        for (int j = i+1; j < n; j++)
        {
            long long k = t |  arr[j];
            m1 = MAX(m1, k);
            t = k;
        }
    }

    for (int i = 0; i < n; i++)
    {
        long long t = brr[i];
        m2 = MAX(m2, t);
        for (int j = i+1; j < n; j++)
        {
            long long k = t |  brr[j];
            m2 = MAX(m2, k);
            t = k;
        }
    }

    printf("%lld\n",m1+m2);
    return 0;
}
