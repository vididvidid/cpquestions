/*
 * File: 1941D.c
 * Author: vididvidid 
 * Created: 2026-07-11 18:48:56
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long val;
    int idx;
} Day;

int comp(const void *p1, const void *p2)
{
    Day *d1 = (Day *) p1;
    Day *d2 = (Day *) p2;
    if (d2->val > d1->val) return 1;
    if (d2->val < d1->val) return -1;
    return 0;
}

void solve()
{
    int n;
    scanf("%d", &n);

    Day *a = (Day *)malloc(n * sizeof(Day));
    Day *b = (Day *)malloc(n * sizeof(Day));
    Day *c = (Day *)malloc(n * sizeof(Day));

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &a[i].val);
        a[i].idx = i;
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &b[i].val);
        b[i].idx = i;
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &c[i].val);
        c[i].idx = i;
    }

    qsort(a, n, sizeof(Day), comp);
    qsort(b, n, sizeof(Day), comp);
    qsort(c, n, sizeof(Day), comp);

    long long mx = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) 
        {
            for (int k = 0; k < 3; k++)
            {
                int day_a = a[i].idx;
                int day_b = b[j].idx;
                int day_c = c[k].idx;

                if (day_a != day_b && day_a != day_c && day_b != day_c) 
                {
                    long long csum = a[i].val + b[j].val + c[k].val;
                    if (csum > mx) {
                        mx = csum;
                    }
                }
            }
        }
    }

    printf("%lld\n", mx);
    free(a);
    free(b);
    free(c);
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

