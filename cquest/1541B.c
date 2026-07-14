/*
 * File: 1541B.c
 * Author: vididvidid 
 * Created: 2026-07-14 15:10:24
 */

/*
 * given n length array with distinct numbers find that ai * aj = i + j
 * n < 10^5 means < O(n) we can go only. 
 * a < 2 *n < 10^5 *2 => 10^10... unsigned long long(%llu)
 *
 * Q. Why 'a' goes till 2*n.., why distinct is there any pattern?
 * Q. In one loop we have to find the all  pairs?
 * 
 *
 * Observations:
 * if there is 1 at any index.. we can get 2 pair.. , but here also O(n^2) :-(
 * ai * aj = i + j => ai * aj - i = j
 *
 * Testcases.. given.. 
 * 1 2 3 4 5
 * 3 1 5 9 2
 *
 * ---------------------------------------------------------------------------
 * Problem Simplification
 * Given an array A of N distinct positive integers where Ai <= 2N, count the
 * number of index pairs (i, j) with 1 <= i < j <= N satisfying:
 *      Ai * Aj = i + j
 *
 * ---------------------------------------------------------------------------
 * Observations:
 * O1: Upper bound on RHS
 *     since indices are 1 based and i < j
 *          max(i + j) = n + (n - 1) = 2n - 1;
 *     Hence,
 *          ai * aj < 2n
 *     and this is also mentioned in constratins.. sum of all testcases < 2*10^5
 *
 * O2: Fix on one index
 *     From 
 *          ai * aj = i + j
 *          j = ai*aj - i
 *     so this means i + j must be multiple ai.
 *     so we don't need to iterate every index just multiple of ai for j.
 *
 * O3: Candidate index
 *     let 
 *          k = aj
 *          j = k * ai - i
 *      for every multiple  
 *          m = ai, 2ai, 3ai,... < 2n
 *      the possible candidate index is
 *          j = m - i
 *      so index is valid only if
 *      -> 1 <= j <= n
 *      -> i < j
 *      -> ai * aj = i + j
 *
 * O4: Complexity
 *     for a fixed ai, the number of multiples below 2n is 2n/ai
 *     total iterations become
 *     sum(v = 1..2n)2n/v => 2n(1 + 1/2 + 1/3 + .. + 1/2n) = O(nlogn).
 *
 * ---------------------------------------------------------------------------
 */ 

#include <stdio.h>

#define int unsigned long long

void solve()
{
    int n;
    scanf("%llu", &n);
    int arr[n + 1];
    for (int i = 1; i <= n; i++)
    {
        scanf("%llu", &arr[i]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int m = arr[i]; m < 2 *n; m += arr[i])
        {
            int j = m - i;

            if (j > i && j <= n)
            {
                if (arr[i] * arr[j] == i + j)
                {
                    ans++;
                }
            }
        }

    }
    printf("%llu\n",ans);
}

signed main()
{
    int t;
    scanf("%llu", &t);

    while (t--)
    {
        solve();
    }
    
    return 0;
}
