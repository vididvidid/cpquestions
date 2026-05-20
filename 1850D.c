/*
 * File: 1850D.c
 * Author: vididvidid 
 * Created: 2026-05-07 00:42:25
 */

/*
 * find the array such that there consecutive elements diff equals to k by
 * removing or rearragning the array..
 *
 * sort the array -> find the consecutive abs difference -> delete the index to
 * the most left that exceeds k and similary the right most that exceeds k ->
 * than print the difference..
 *
 * 0    1   2   3   4   5   6   7    
 * 17   3   1   20  12  5   17  12  -> unsorted array
 * 1    3   5   12  12  17  17  20  -> sorted array
 *   2    2   7   0   5   0   3     -> consecutive diffierence..
 *............XXXXXXXXXXXXXXXXXXXX
 * [....3....]  [.2.]  [ ...3... ]
 *
 *  0   1   2   3   4   5   6
 *  2   2   7   0   5   0   3
 *  (0,1)     (3,3)    (5,6)
 *  1-0+2=3   3-3+2=2   6-5+2 = 3
 *
 * 0    1   2   3   4
 * 2    3   8   10  19
 *   1    5   2   9    
 * .......XXXXXXXXXXXX
 * [..2..]  [.2.]
 *
 *  0   1   2   3
 *  1   5   2   9
 * (0,0)  (2,2)
 * 0-0+2=2  2-2+2 = 2
 *
 * 0    1   2   3   4   5   6   7
 * 8    3   1   4   5   10  7   3
 * 1    3   3   4   5   7   8   10
 *   2    0   1   1   2   1   2
 *     [......4.....]  [..2..]
 *
 *  0   1   2   3   4   5   6
 *  2   0   1   1   2   1   2
 *     (1,3).....     (5,5)
 *     3-1+2= 4        (5-5+2=2)
 */

#include <stdio.h>
#include <limits.h>

#ifdef LOCAL_DEBUG
    #define debug(fmt,...) \
        fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)

    #define debug_arr(msg, arr, n) \
        do { \
            fprintf(stderr, "[DEBUG] %s: ",msg); \
            for (int _i = 0; _i < (n); _i++) \
                fprintf(stderr, "%d ",(arr)[_i]);\
            fprintf(stderr,"\n"); \
        } while (0)
#else
    #define debug(fmt, ...)
    #define debug_arr(msg,arr,n)

#endif

#define MAX(a,b) (a)>(b)?(a):(b)

void qsort(int *start, int *end)
{
    if (start >= end) return;
    int pivot = *(start + (end - start) /2);
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
    qsort(start,high);
    qsort(low,end);
}

void solve()
{
    int n, k;
    scanf("%d %d",&n,&k);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    
    debug_arr("Initial Array", arr, n);

    qsort(arr,arr+(n-1));

    debug_arr("Sorted Array", arr, n);

    for (int i = 1; i < n; i++)
    {
        int t = arr[i]-arr[i-1];
        arr[i-1] = t;
    }
    arr[n-1] = -1;
    
    debug_arr("Difference Array", arr, n);

    int ans = INT_MIN, start = -1, end = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] != -1)
        {
            if (arr[i] <= k)
            {
                if(start == -1) start = i;
            }
            else
            {
                end = i - 1;
                if (start != -1 && end != -1)
                {
                    debug("Start: %d, End: %d",start, end);
                    ans = MAX(ans, (end - start + 2));
                }
                start = -1;
                end = -1;
            }
        }
    }
    if ( end == -1) 
    {
        /* if (ans == INT_MIN) */
        /*     ans = MAX(ans,n); */
        
         if (start != -1)
        {
            end = n-2;
            debug("IF: Start: %d, End: %d", start, end);
            ans = MAX(ans, (end - start + 2));
        }
         else if (start == -1 && ans == INT_MIN)
         {
             debug("IF: ANS = 1");
             ans = 1;
         }
    }
    debug("ANS: %d",ans);
    printf("%d\n",n-ans);
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
