/*
 * File: 1406B.c
 * Author: vididvidid 
 * Created: 2026-07-15 19:05:39
 */

/*
 * you are given an array with n integers. find the max ai*aj*ak*al*at among all
 * five indices
 * n [5,10^5] => O(n) or O(nlogn)
 *
 * sorting it and choosing the last five will not work
 * testcase example
 * 6
 * -1 -2 -3 1 2 -1
 *  output : 12 (-1 -2 -3 2 -1)
 *  they haven't took 1 because two -1 will give plus 1.. if we choose 1 than -1
 *  will be there which will give (-1 -2 -3 1 2) = -12
 *
 * negative values need to be considered
 *
 * if no of positive >= 5 no of negative <= 1 :
 *  => than choose only positive number after sorting.
 * if no of positive >= 5 no of negative >= 1 :
 *  ... 
 *  can't go like that too many cases.. 
 *
 *  can we go with prefix multiple
 *
 *  -1 -1 -2 -3 => -3 -2 -1 -1 => [-3, 6, -6, 6];
 *  1 2 => descending => 2 1 => [2 2];
 *
 *  but if all negative than print multiple of all if all positive than print
 *  all.
 *
 */
#include <stdio.h>

void sort(int arr[], int start, int end)
{
    if (start >= end) return;
    int mid = arr[(start + (end - start) / 2)];
    int low = start, high = end;
    while (low < end)
    {
        while (arr[low] < mid) low++;
        while (arr[high] > mid) high--;
        while (low <= high)
        {
            int tmp = arr[low]; arr[low] = arr[high]; arr[high] = tmp;
            low++; high--;
        }
    }

    sort(arr, start, high);
    sort(arr, low, end);
}

void solve()
{
    int n;
    scanf("%d", &n);
    int nrr[n], arr[n];
    int neg = 0, pos = 0, ans = 0;
    for (int i = 0; i < n; i++)
    {
        int num;
        scanf("%d", &num);
        if (num < 0)
        {
            nrr[neg++] = num;
        }
        else
        {
            arr[pos++] = num;
        }
    }

    if ((neg == 5 && pos == 0)|| (pos == 5 && neg == 0))
    {
        for (int i = 0; i < 5; i++)
        {
            if (neg > 0)
            {
                ans *= nrr[i];
            }
            else
            {
                ans *= arr[i];
            }
        }

        printf("%d\n",ans);
    }


}

signed main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }

    return 0;
}
