/*
 * File: 1005C.c
 * Author: vididvidid 
 * Created: 2026-10-30 23:10:14
 */

/*
 * given a list of numbers, find how many number do not have a pair
 * in the list that adds up to a power of 2. you need to remove those
 * numbers.
 *
 * for each number, we need to check if there is a matching number 
 * that makes their sum a power of 2 (like 2, 4, 8 , 16,.. up to 2^31)
 * To do this quickly, we first sort the list. Then, for every number
 * and every possible power of 2, we use binary search to look for 
 * the required matching number. Count how many numbers fail to find
 * a match.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare (const void *a, const void *b) 
{
    int val1 = *(const int *)a;
    int val2 = *(const int *)b;
    if (val1 < val2) return -1;
    if (val1 > val2) return 1;
    return 0;
}

bool has_pair(int *a, int n, int i, long long target)
{
    int left = 0, right = n -1;
    while (left <= right)
    {
        int mid = left + (right - left) /2;
        if (a[mid] == target)
        {
            if (mid != i) return true;
            if (mid > 0 && a[mid - 1] == target) return true;
            if (mid < n - 1 && a[mid + 1] == target) return true;
            return false;
        } else if (a[mid] < target) 
        {
            left = mid + 1;
        } else 
        {
            right = mid - 1;
        }
    }

    return false;
}


void solve() 
{
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int remove_count = 0;

    for (int i = 0; i < n; i++)
    {
        bool found_pair = false;
        for (int d = 0; d <= 31; d++)
        {
            long long target = (1LL << d) - a[i];
            if (target <= 0) continue;

            if (has_pair(a, n, i, target)) 
            {
                found_pair = true;
                break;
            }
        }

        if (!found_pair)
        {
            remove_count++;
        }
    }

    printf("%d\n", remove_count);
}

int main()
{
    solve();
    return 0;
}
