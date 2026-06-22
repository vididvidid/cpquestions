/*
 * File: 1471B.c
 * Author: vididvidid 
 * Created: 2026-06-22 17:18:56
 */

/*
 * given an array a of length n, find the sum of the array in final if the after
 * doing operation till a[i] is not divisible by x. if its divisible add the
 * a[i]/x , a[i]/x times at the end of the array.
 *
 *  t [1, 100]
 *  n [1, 10^5], x [2, 10^9]
 *  a[i] [1, 10^9]
 *
 *  we can only afford < O(n)
 *  
 */

#include <stdio.h>
#include <limits.h>

#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)

void solve()
{
    int n;
    scanf("%d",&n);
    long long x, arr[n];
    scanf("%lld", &x);
    
    int flag = 0, flag1 = 0, ndiv = INT_MAX, adsum = 0;
    long long sum = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);

        int div = 0;
        long long temp = arr[i];
        while (temp > 1 && temp % x == 0)
        {
            temp /= x;
            div++;
        }
        int tp = ndiv;
        ndiv = MIN(ndiv, div);
        if (tp != ndiv)
        {
            flag1 = i;
        }
        
        if (!flag) sum += arr[i];

        if (!flag && arr[i] % x != 0)
        {
            flag = i;
        }
    }
    //debug
    /* printf("`/ end: %d sum: %lld ndiv: %d ndivlup: %d\n",flag, sum, ndiv, flag1); */

    /* if (flag) */ 
    /* { */
    /*     printf("%lld\n",sum); */
    /*     return; */
    /* } */
    /* else */ 
    /* { */
        sum = 0;
        for (int i = 0; i < n; i++)
        {
            if (i < flag1)
            {
               long long temp = arr[i] * (ndiv + 2);
               sum += temp;
               /* printf("`/ i > %d temp > %lld sum > %lld\n",i, temp, sum); */
            }
            else
            {
                long long temp = arr[i] * (ndiv + 1);
                sum += temp;
                /* printf("`/ i > %d temp > %lld sum > %lld\n",i, temp, sum); */
            }
        }        

        printf("%lld\n",sum);
    /* } */

}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}
