/*
 * File: 1763B.c
 * Author: vididvidid 
 * Created: 2026-07-13 19:48:16
 */

/*
 * n monsters -> hi (health) and pi (power)
 * can reduce all monsters health by k in single attack
 * monster attack reduces k by minimum of weakest monster pi
 *
 * n, k => 10^5 => O(n) or O(nlogn) 
 * h, p => 10^9 => long long
 *
 * print yes or no just that
 *
 * -------------------------------------------------------------
 * Question in simple form
 *
 * you are given N elements, where ith element has a value Hi, and a weight Pi.
 * You are also given an initial integer K.
 * you repeat the follwoing oprn while K > 0:
 * 1. subtract K from Hi for all existing elements.
 * 2. Remove all elements where Hi <= 0
 * 3. If the set of elements is now empty, stop and output YES
 * 4. Otherwise, find the minimum Pi among all remaining elements, subtract the
 * minimum from K, and repeat
 *
 * if the loop terminates because K <= 0 while elements still remain, output NO.
 *
 *
 */

#include <stdio.h>

#define int long long

typedef struct {
    int h;
    int p;
} mnstr;

void sort(mnstr *arr, int start, int end)
{
    if (start >= end) return;
    int mid = arr[start + (end - start) / 2].p;
    int low = start, high = end;
    while (low <= high)
    {
        while (arr[low].p < mid) low++;
        while (arr[high].p > mid) high--;
        if (low <= high)
        {
            mnstr tmp = arr[low];
            arr[low] = arr[high];
            arr[high] = tmp;
            low++;
            high--;
        }
    }

    sort(arr, start, high);
    sort(arr, low, end);
}


void solve()
{
    int n, k;
    scanf("%lld %lld", &n, &k);

    mnstr mrr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &mrr[i].h);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &mrr[i].p);
    }

    sort(mrr, 0, n - 1);
    
    int dmg = 0, idx = 0;
    while (k > 0 && idx < n)
    {
        dmg += k;

        while (idx < n && mrr[idx].h <= dmg) 
        {
            idx++;
        }

        if (idx < n)
        {
            k -= mrr[idx].p;
        }
    }

    if (idx == n) {
        printf("YES\n");
    }
    else
    {
       printf("NO\n");
    }

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
