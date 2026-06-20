/*
 * File: 1933C.c
 * Author: vididvidid 
 * Created: 2026-06-20 10:58:15
 */

/*
 * find all the possibel combination l = k * a ^ x * b ^y is valid
 *
 * max value of x when y = 0 is x = [ log base a (l) ]
 */

#include <stdio.h>
#include <math.h>

#define int long long

int mx(int l, int b)
{
    return (int)floor(log((double)l) / log((double)b) + 1e-9);
}

void solve()
{
    int a, b, l;
    scanf("%lld %lld %lld", &a, &b, &l);
    int arr[1000];

    int mxx = mx(l, a);
    int mxy = mx(l, b);

    int ans = 0;

    for (int i = 0; i <= mxx; i++)
    {
        for (int j = 0; j <= mxy; j++)
        {
            int k = (int)round(pow(a,i)) * (int)round(pow(b, j));
            if (k > 0 && k <= l && l % k == 0)
            {
                int val = l / k;
                int flag = 0;
                for (int m = 0; m < ans; m++)
                {
                    if (arr[m] == val)
                    {
                        flag = 1;
                        break;
                    }
                }

                if (!flag)
                {
                    arr[ans] = val;
                    ans++;
                }
            }
        }
    }

    printf("%lld\n", ans);
}

signed main()
{
    int t;
    scanf("%lld ", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}
