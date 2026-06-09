/*
 * File: 2208B.c
 * Author: vididvidid 
 * Created: 2026-06-09 22:18:19
 */

#include <stdio.h>
#include <stdlib.h>

int compare (const void *a, const void *b) {
    long long num1 = *(const long long *)a;
    long long num2 = *(const long long *)b;
    if (num1 < num2) return -1;
    if (num1 > num2) return 1;
    return 0;
}

void solve()
{
    long long n, k, p, m;
    scanf("%lld %lld %lld %lld", &n, &k, &p, &m);

    long long a[5005];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &a[i]);
    }

    long long cf = a[p - 1];
    if (p > k) {
        long long fp[5005];
        for (int i = 0; i < p - 1; i++) {
            fp[i] = a[i];
        }

        qsort(fp, p - 1, sizeof(long long), compare);

        for (int i = 0; i < p - k; i++) {
            cf += fp[i];
        }
    }

    if (m < cf) {
        printf("0\n");
        return;
    }

    long long ans = 1;
    m -= cf;

    long long cs = a[p - 1];
    if (n > k) 
    {
        long long oc[5005];
        int idx = 0;

        for (int i = 0; i < n; i++){
            if (i != p - 1) {
                oc [idx++] = a[i];
            }
        }

        qsort(oc, n - 1, sizeof(long long), compare);

        for (int i = 0; i < n - k; i++) {
            cs += oc[i];
        }
    }

    ans += m / cs;

    printf("%lld\n",ans);
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
