/*
 * File: 2008D.c
 * Author: vididvidid 
 * Created: 2026-07-21 16:24:10
 */

/*
 * Given a permutation P of size N and a binary string S of size N, output array
 * F where F(i) is the number of indices j in the same permutation cycle as i
 * such that Sj = '0'.
 *
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    int n;
    scanf("%d", &n);
    n++;
    int arr[n], visited[n], ans[n], cycle[n];
    memset(arr, 0, sizeof(arr));
    memset(visited, 0, sizeof(visited));
    memset(ans, 0, sizeof(ans));
    memset(cycle, 0, sizeof(ans));

    char s[n+1];
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    scanf("%s", &s[1]);

    int curr = 0, idx = 0, bc = 0;
    for (int i = 1; i < n; i++)
    {
       if (visited[i]) continue;
       curr = i; 
       idx = 0;
       bc = 0;
       while (!visited[curr])
       {
          visited[curr] = 1;
          cycle[idx++] = curr; 
          if (s[curr] == '0') bc++;
          curr = arr[curr];
       }

       for (int j = 0; j < idx; j++)
       {
           ans[cycle[j]] = bc;
       }
    }
    
    for (int i = 1; i < n; i++)
    {
        printf("%d ", ans[i]);
    }
    printf("\n");

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
