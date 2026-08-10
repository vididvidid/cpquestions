/*
 * File: 2072D.c
 * Author: vididvidid 
 * Created: 2026-08-10 20:18:02
 */

/*
 * array of length n, minimize the num of inverstion (i < j and bi > bj)
 * oprn : only one time -> select l and r and cyclic rotate it
 *
 * n , a < 2000
 * we can go for the n^2
 * but the question is how to change array everytime in O(1)
 *
 * like first we take 0 to (n, 0] -> do cycle -> calculate inversion
 *                    1 to (n, 1] 
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 2001

int arr[MAXN];
int tmp[MAXN];
int n  = 0, l = 0, r = 0;
int ans = INT_MAX, tans = INT_MAX;

void initialize();
void input();
void rotate(int arr[], int l, int r);
int inversion(int arr[]);
void logic();

void solve()
{
    initialize();
    input();
    logic();
    printf("%d %d\n",l + 1, r + 1);
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

void initialize()
{
    memset(arr, 0, sizeof(arr));
    memset(tmp, 0, sizeof(tmp));
    ans = INT_MAX;
    tans = INT_MAX; 
    n = 0;
    l = 0;
    r = 0;
}

void input()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        tmp[i] = arr[i];
    }
}

void rotate(int arr[], int l, int r)
{
    int temp = arr[l];
    for (int i = l; i < r; i++)
    {
        arr[i] = arr[i + 1];
    }
    arr[r] = temp;
}

int inversion(int arr[])
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j]) cnt++;
        }
    }

    return cnt;
}

void reset(int arr[], int tmp[])
{
    for (int i = 0; i < n; i++)
    {
        tmp[i] = arr[i];
    }
}

void logic()
{
    ans = inversion(arr);
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            reset(arr, tmp);
            rotate(tmp, i, j);
            tans = inversion(tmp);
            if (tans < ans)
            {
                ans = tans;
                l = i;
                r = j;
            }
        }
    }
}


