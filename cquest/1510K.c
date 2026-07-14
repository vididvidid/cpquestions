/*
 * File: 1510K.c
 * Author: vididvidid 
 * Created: 2026-07-14 17:40:21
 */

/*
 * given an 2n length array you have to sort it in min oprn.. 
 * swap p1 to p2.. or p1 to pn+1 .. 
 * if after operation sorted print number else -1
 * 
 * n < 1000 so we can go O(n^2) and all..
 *
 * observation..
 * because we have 2nd operation replace i to n + i.. that's beneficial in min
 * because if we collect all big numbers on the left than with this operation
 * we can make them to right in one go.. 
 * and then using operation 1 we can swap it.. 
 * so at the end i think goal is if we can maximize bringing the big number on
 * left side than use operation 2 and than with operation 1 sort it. 
 *
 * Q when its is not able to be sorted.. 
 * testcase example
 * 3 4 2 1 -> 4 3 1 2 (O1)-> 1 3 4 2(O2) -> 1 3 2 4 (O1) -> 1 2 3 4 (O1)
 * wait it got sorted but in example its -1 why?
 *
 * i am reading question wrong.
 *
 * 1. all pairs will be swaped not isolted one.. 
 * 2. we have to use op1 and op2 in pair if used isolated will form closed loop
 *
 * ---------------------------------------------------------------------------
 * Problem Simplification
 * you are given an array P of length 2n containing a permutation from 1 to 2n.
 * you can perform two operations.
 * op1 : swap adjacent pairs: (p1, p2), (p3, p4).. 
 * op2 : swap the left half to right half: (p1, pn+1), (p2, pn+2)...
 * find the minimum number of operations required to sort P in ascending order,
 * or output -1 if it is impossible.
 *
 * Contraints
 * n <= 1000 => 2n = 2000 : O(n^2) => (2000)^2 => 4 * 10^6
 *
 * ---------------------------------------------------------------------------
 *  Observations:
 *  1. pair swaps are global not isolated; whole array will be affected with op
 *  2. if used only single op again and again will result in the closed loop
 */

#include <stdio.h>
#include <stdbool.h>

#define MIN(a,b) (a)<(b)?(a):(b)

bool is_sorted(int arr[], int len)
{
    for (int i = 1; i <= len; i++)
    {
        if (arr[i] != i) return false;
    }

    return true;
}

int simulate(int orig[], int n, int start_op)
{
    int len = 2 * n;
    int arr[len + 1];
    for (int i = 1; i <= len; i++) arr[i] = orig[i];

    if (is_sorted(arr, len)) return 0;

    int current_op = start_op;
    for (int step = 1; step <= len; step++)
    {
        if (current_op == 1)
        {
            for (int j = 1; j < len; j += 2)
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            current_op = 2;
        }
        else
        {
            for (int j = 1; j <= n; j++)
            {
                int temp = arr[j];
                arr[j] = arr[j + n];
                arr[j + n] = temp;
            }
            current_op = 1;
        }

        if (is_sorted(arr, len)) {
            return step;
        }
    }

    return -1;
}


void solve()
{
    int n;
    scanf("%d", &n);
    int arr[ 2 * n + 1];
    for (int i = 1; i <= 2 *n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int path_a = simulate(arr, n, 1);
    int path_b = simulate(arr, n, 2);

    if (path_a == -1 && path_b == -1) {
        printf("-1\n");
    } else if (path_a == -1) {
        printf("%d\n", path_b);
    } else if (path_b == -1) {
        printf("%d\n", path_a);
    }
    else
    {
        printf("%d\n", MIN(path_a, path_b));
    }
}

int main()
{
    solve();
    return 0;
}
