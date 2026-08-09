/*
 * File: 2242C.c
 * Author: vididvidid 
 * Created: 2026-08-09 22:19:33
 */

/*
 * given -> sorted array
 * oprn : -> mark all the element ai != a(i-1)
 *        -> either delete those number or duplicate it
 * find total number of length k array possible
 *
 * n, k <= 3 * 10^5 (O(n) or O(nlogn))
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define int long long

#undef int
int cmp(const void *a, const void *b) 
{
    long long diff = *(long long*)a - *(long long*)b;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}
#define int long long
void solve()
{
    int n, k;
    scanf("%lld %lld", &n, &k);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
    }

    int freq[n];
    int idx = 0, count = 1;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] == arr[i - 1])
        {
            count++;
        } else {
            freq[idx++] = count;
            count = 1;
        }
    }

    freq[idx++] = count;

    qsort(freq, idx, sizeof(int), cmp);

    int sum[idx + 1];
    sum[idx] = 0;
    for (int i = idx - 1; i >= 0; i--)
    {
        sum[i] = sum[i + 1] + freq[i];
    }

    int ans = 0;

    for (int i = 0; i < idx; i++)
    {
        if (i == 0 || freq[i] != freq[i - 1]){
            int s = idx - i;
            int v = sum[i];
            int diff = k - v;

            if (diff % s == 0)
            {
                int d = diff / s;

                if (freq[i] + d >= 1)
                {
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
    scanf("%lld", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}

