/*
 * File: 558A.c
 * Author: vididvidid 
 * Created: 2026-07-03 15:22:23
 */

#include <stdio.h>

void qsort(int arr[][2], int start, int end)
{
    if (start >= end) return;
    int pivot = arr[(start + (end - start) / 2)][0];
    int low = start, high = end;
    while (low <= high)
    {
        while (arr[low][0] < pivot) low++;
        while (arr[high][0] > pivot) high--;
        if (low <= high)
        {
            int tmp = arr[low][0]; arr[low][0] = arr[high][0];arr[high][0] = tmp;

            int tp = arr[low][1]; arr[low][1] = arr[high][1]; arr[high][1] = tp;
            low++; high--;
        }
    }

    qsort(arr, low, end);
    qsort(arr, start, high);
}

void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n][2];
    int nc = 0, pc = 0, neg = 0, pos = 0, cont = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &arr[i][0], &arr[i][1]);
        if (arr[i][0] > 0) pos++;
        else neg++;
    }

    qsort(arr,0,n - 1);

    int sum = 0;

    if (pos == neg) {
        for (int i = 0; i < n; i++) sum += arr[i][1];
    }
    else if (pos > neg) {
        for (int i = 0; i< neg; i++) sum += arr[i][1];
        for (int i = neg; i < neg + neg + 1; i++) sum += arr[i][1];
    }
    else {
        for (int i = neg; i < n; i++) sum += arr[i][1];
        for (int i = neg -1; i >= neg - 1 - pos; i--) sum += arr[i][1];
    }
    
    printf("%d\n",sum);
}

int main()
{
    solve();
    return 0;
}
