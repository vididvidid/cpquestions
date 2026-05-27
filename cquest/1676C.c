/*
 * File: 1676C.c
 * Author: vididvidid 
 * Created: 2026-04-17 16:00:52
 */

// find the difference between all pair of words and return the minimum..
// and the move part i don't understand lets first see if that works..
//

#include <stdio.h>
#include <limits.h>

#define ABS(a) (a)<0? -1 *(a) : (a)
#define MIN(a,b) (a)<(b) ? (a) : (b)

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);
    char s[n][m+1];
    for (int i = 0; i < n; i++) scanf("%s",s[i]);

    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < m; k++){
                sum += ABS((int)s[i][k] - (int)s[j][k]);
            }
            min = MIN(min,sum);
        }
    }

    printf("%d\n",min);
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
