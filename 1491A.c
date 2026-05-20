/*
 * File: 1491A.c
 * Author: vididvidid 
 * Created: 2026-04-25 12:08:39
 */

#include <stdio.h>

void qsort(int *start, int *end)
{
    if (start >= end) return;
    int pivot = *(start + (end - start) / 2);
    int *low = start, *high = end;
    while (low <= high)
    {
        while (*low > pivot) low++;
        while (*high < pivot) high--;
        if (low <= high)
        {
            int tmp = *low; *low = *high; *high = tmp;
            low++; high--;
        }
    }
    qsort(start, high);
    qsort(low, end);
}

int main()
{
    int n, q;
    scanf("%d %d",&n, &q);
    int arr[n+1];
    arr[0] = -1;
    int c1 = 0, c0 = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d",&arr[i]);
        if (arr[i] == 1) c1++;
        else c0++;
    }
    while (q--)
    {
        int ord, val;
        scanf("%d %d",&ord, &val);
        if (ord == 1){
            int tmp = 1 - arr[val];
            arr[val] = tmp;
            if (arr[val] == 1) c1++,c0--;
            else c1--,c0++;
        } else {
            if (val <= c1) printf("1\n");
            else printf("0\n");
        }
    }
    return 0;
}

