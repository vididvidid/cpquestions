/*
 * File: 1561A.c
 * Author: vididvidid 
 * Created: 2026-04-25 03:34:14
 */

/*
 * find when the array will be sorted.. using custom sorting function..
 *
 * custSort: (arr, n, count)
 *  if sorted(arr) : return count
 *  if count is odd:
 *      iterate over the array at odd indices and swap
 *  if count is even:
 *      iterate ver teh array at even indices and swap
 */

#include <stdio.h>


void swap(int *arr, int *brr)
{
    int tmp = *arr;
    *arr = *brr;
    *brr = tmp;
}

int sorted(int *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > arr[i+1]) return 1;
    }
    return 0;
}

int custSort(int *arr, int n)
{
    int count = 1; 
    while (sorted(arr,n)) 
    {
       if (count++ % 2 == 0)
       {
           for (int i = 1; i < n; i++) {
               if (i % 2 == 0) {
                   if (arr[i] > arr[i+1])
                   swap(&arr[i], &arr[i+1]);
               }
           }      
       } else 
       {
           for (int i = 1; i < n - 1; i++) {
               if (i % 2 != 0) {
                   if (arr[i] > arr[i+1])
                   swap(&arr[i], &arr[i+1]);
               }
           } 
       }
       /* for (int i = 1; i <= n; i++) printf("%d ",arr[i]); */
       printf("\n");
    }
    return count;
}

void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n+1];
    arr[0] = -1;
    for (int i = 1; i <= n; i++) scanf("%d",&arr[i]);
    /* printf("DEBUG: -----\n"); */
    /* for (int i = 0; i <= n; i++) printf("%d ",arr[i]); */
    /* printf("\n"); */
    int ans = custSort(arr,n);
    /* for (int i = 0; i <= n; i++) printf("%d ",arr[i]); */
    /* printf("\n"); */
    printf("%d\n",ans-1);
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
