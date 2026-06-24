/*
 * File: 1623B.c
 * Author: vididvidid 
 * Created: 2026-06-24 18:31:53
 */

/* 
 * you are given N intervals formed by recursiverly partiioning the array [1,
 * N]. Each interval [L, R] was split at a hidden pivot d (L <= d <= R) to
 * create two intervals: [L, d - 1] and [d + 1 , R]. Find the pivot d for each
 * interval.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Range {
    int l;
    int r;
};

int comp (const void *a, const void *b) {
    struct Range *rangeA = (struct Range *) a;
    struct Range *rangeB = (struct Range *) b;
    int lenA = rangeA->r - rangeA->l;
    int lenB = rangeB->r - rangeB->l;
    return lenA - lenB;
}

void solve()
{
    int n;
    scanf("%d", &n);
    struct Range ranges[1005];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &ranges[i].l, &ranges[i].r);
    }

    qsort(ranges, n, sizeof(struct Range), comp);

    int used[1005] = {0};

    for (int i = 0; i < n; i++)
    {
        int l = ranges[i].l;
        int r = ranges[i].r;
        int d = -1;

        for (int j = l; j <= r; j++)
        {
            if (used[j] == 0) {
                d = j;
                used[j] = 1;
                break;
            }
        }


        printf("%d %d %d\n", l, r, d);
    }

    printf("\n");
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
