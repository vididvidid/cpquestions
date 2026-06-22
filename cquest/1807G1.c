/*
 * File: 1807G1.c
 * Author: vididvidid 
 * Created: 2026-06-22 12:40:16
 */

/*
 * given array c check if it contains the follwoing situation:
 * array started as a single element 1 and it kept on adding new elment just
 * fomr the subsequence of the array and its sum.. 
 *
 * (a + b)/2 => a/2 + b/2 = a + ()
 */

#include <stdio.h>

void sort(int *start, int *end)
{
    if (start >= end) return;
    int pivot = *(start + (end - start) / 2);
    int *low = start, *high = end;
    while (low <= high)
    {
        while (*low < pivot) low++;
        while (*high > pivot) high--;
        if (low <= high)
        {
            int tmp = *low; *low = *high; *high = tmp;
            low++;high--;
        }
    }

    if (low < end) sort(low, end);
    if (start < high) sort(start, high);
}

void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    sort(arr, arr+n - 1);

    int sum = arr[0];
    if (arr[0] != 1)
    {
        printf("NO\n");
        return;
    }
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > sum)
        {
            printf("NO\n");
            return;
        }
        if (arr[i] <= sum)
        {
            sum += arr[i];
        }
    }

    printf("YES\n");
    return;
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

