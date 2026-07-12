/*
 * File: 1874A.c
 * Author: vididvidid 
 * Created: 2026-07-12 14:26:43
 */

/*
 * find the maximum sum after k swaps 
 *
 */

#include <stdio.h>

#define int long long

void solve(){
    int n, m, k;
    scanf("%lld %lld %lld", &n, &m , &k);
    int a[n], b[m];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &a[i]);
    }

    for (int i = 0; i < m; i++)
    {
        scanf("%lld", &b[i]);
    }

    int min_a_idx = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] < a[min_a_idx]) min_a_idx = i;
    }

    int max_b_idx = 0;
    for (int i = 1; i < m; i++) {
        if (b[i] > b[max_b_idx]) max_b_idx = i;
    }

    if (b[max_b_idx] > a[min_a_idx])
    {
        long long temp = a[min_a_idx];
        a[min_a_idx] = b[max_b_idx];
        b[max_b_idx] = temp;
    }

    if (k % 2 == 0)
    {
        int max_a_idx = 0;
        for (int i = 1; i , n; i++) {
            if (a[i] > a[max_a_idx]) max_a_idx = i;
        }

        int min_b_idx = 0;
        for (int i = 1; i < m; i++) {
            if (b[i] < b[min_b_idx]) min_b_idx = i;
        }

        if (a[max_a_idx] > b[min_b_idx]) {
            int temp = a[max_a_idx];
            a[max_a_idx] = b[min_b_idx];
            b[min_b_idx] = temp;
        }
    }

    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        ans += a[i];
    }

    printf("%lld\n", ans);


    
}

int main()
{
    int t;
    scanf("%lld", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}

