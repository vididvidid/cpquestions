/*
 * File: 1898A.c
 * Author: vididvidid 
 * Created: 2026-04-22 13:22:00
 */

/*
 * store the count of B and the index
 * so if the coB > demand  like 4 > 2 so from [ 1 to arr(count - 2) ]
 * ex. 5 3 BBBBA
 * so arr = [4,1,2,3,4,x];
 * now ans will be [1 to arr(arr[0]-demand)] => [1 to arr[4-3]] => 1 
 */

#include <stdio.h>

#define ABS(a) (a)<0?-1 *(a): (a)

void solve()
{
    int n, m;
    scanf("%d %d",&n,&m);
    int arr[n+1];
    for (int i = 0; i <= n; i++) arr[i] = 0;
    for (int i = 1; i <= n; i++)
    {
        char c;
        scanf(" %c",&c);
        if (c == 'B')
        {
            arr[0]++;
            arr[arr[0]] = i;
        }
    }
    if (arr[0] == m) 
    {
        printf("0\n");
    } else if (arr[0] > m)
    {
        printf("1\n");
        printf("%d A\n",arr[arr[0]-m]);
    } else 
    {
        printf("1\n");
        int k=0,cn = 0;
        for (int i = 1; i <= arr[0]; i++)
        {
            if (i == 1)
            {
                cn += arr[i] - 1;
            } else {
                cn += (arr[i] - arr[i-1] - 1);
            }
            if (cn >= (m-arr[0])) 
            {
                /* printf("DEBUG: i: %d cn: %d m-arr[0]: %d\n",i,cn,m-arr[0]); */
                /* if ( i - 1 == 0 ) printf("1 B\n"); */
                /* else */ 
                printf("%d B\n",arr[i]-(cn-(m-arr[0]))-1);
                k =1;
                break;
            }
        }
        if (k != 1)
        {
            /* printf("DEBUG: arr[arr[0]]: %d cn: %d m-arr[0]:%d\n",arr[arr[0]],cn,m-arr[0]); */
            int temp = ABS(cn - (m-arr[0]));
            printf("%d B\n",arr[arr[0]]+temp);
        }
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
