/*
 * File: 1644A.c
 * Author: vididvidid 
 * Created: 2026-04-24 04:32:17
 */

/*
 * permuation of all the number from 1 to n that are anti fibonacci..
 * for (1 to n ):
 *  recursive calls.. (arr, index, n )
 *      base case : if index == n print and return;
 *      iterate over the 1 to n:
 *          check if it is containg or not.. if containg skip..
 *          else :
 *              check if the last two element sum is the current element 
 *              if it is continue
 *              else :
 *                  put that number and call the recurisve..
 *
 * check (arr, index, n, i):
 *  for (int i = 1; i <= index; i++):
 *      if (arr[i] == i)
 *          return ture;
 *  return true;
 *
 * recur (arr, index , n):
 *  base case : if index == n: print the array and return;
 *  for (i:  1 to n ) :
 *      if (check(arr, index,n, i)) continue;
 *      else :
 *          if( index > 2 && sum(arr[index-1]+arr[index-2]) == i) continue;
 *          else : 
 *              arr[++index] = i;
 *              recur(arr,index, n);
 *
 *
 * arr[n];
 * for ( 1 to n ):
 *      arr[0] = i;
 *      recur(arr, 1, n );
 *
 */

#include <stdio.h>
int count = 0;

int check(int *arr, int index, int i, int n)
{
    for (int j = 0; j < index; j++)
    {
        if (arr[j] == i) return 1;
    }
    return 0;
}

void recur(int *arr, int index, int n)
{
    if (count == 0) return;
    if ( index >= n){
        for (int i = 0; i < n ; i++){
            printf("%d ",arr[i]);
        }
        printf("\n");
        count--;
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (check (arr, index, i, n)) continue;
        else 
        {
            if (index >= 2 && (arr[index-1] + arr[index-2] == i)) continue;
            else 
            {
                arr[index++] = i;
                recur(arr, index, n);
                index--;
            }
        }
    }
}

void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    count = n;
    for (int i = 1; i <= n; i++)
    {
        arr[0] = i;
        recur(arr, 1, n);
    }
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
