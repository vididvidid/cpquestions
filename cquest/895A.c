/*
 * File: 895A.c
 * Author: vididvidid 
 * Created: 2026-07-17 06:30:43
 */

/*
 * pizza in n pieces.
 * ith piece -> sector of an angle equal to ai.
 * divide all pieces -> two continous sectors -> diff(angle of sectors) -> min
 * sector angle is sum of angles of all piece in it.
 * one sectors can be empty
 *
 */
#include <stdio.h>
#include <limits.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define ABS(a) ((a)>0?(a):-1*(a))

void sort(int arr[], int start, int end)
{
    if (start >= end) return;
    int mid = arr[(start + (end - start) / 2)];
    int low = start, high = end;
    while (low <= high)
    {
        while (arr[low] > mid) low++;
        while (arr[high] < mid) high--;
        if (low <= high)
        {
            int tmp = arr[low]; arr[low] = arr[high]; arr[high] = tmp;
            low++; high--;
        }
    }

    sort(arr , start, high);
    sort(arr , low, end);
}

void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }

    sort(arr, 0, n - 1);

    int ans = INT_MAX;
    int t1 = 0, t2 = 0;
    for (int i = 0; i <n; i++)
    {
        if (t1 <= t2) t1 += arr[i];
        else t2 += arr[i];
    }

    printf("%d\n",ABS(t1-t2));
}

int main()
{
    solve();
    return 0;
}
