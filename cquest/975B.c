/*
 * File: 975B.c
 * Author: vididvidid 
 * Created: 2026-06-27 19:08:38
 */

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) (a)>(b)?(a):(b)
#define int long long

int nstick (int org, int j, int i, int s, int n) {
    int base = s / n;
    int rem = s % n;

    int dis = (j - i - 1 + n)  % n;

    int add = base + (dis < rem ? 1 : 0);

    if (j == i) {
        return add;
    }

    return org + add;
}
void solve()
{
    int arr[14] = {0}, prr[14] = {0};
    int n = 14;
    for (int i = 0; i < n; i++) scanf("%lld",&arr[i]);

    int ans = LLONG_MIN;
    for (int i = 0; i < n; i++)
    {

        if (arr[i] > 0)
        {


            for (int j = 0; j < n; j++ ) prr[j] = arr[j];
            int count = 0;

            for (int j = 0; j < n; j++)
            {
                prr[j] = nstick(prr[j], j, i, arr[i], n);
            }

            for (int j = 0; j < n; j++)
            {
                if (prr[j] % 2 == 0)
                {
                    count += prr[j];
                }
            }
            ans = MAX(count, ans);
        }
        /* printf("\n"); */
        /* for (int j = 0; j < n; j++) printf("%lld\t",prr[j]); */
        /* printf("\n"); */
    }

    printf("%lld\n",ans);
}

int main()
{
    solve();
    return 0;
}
