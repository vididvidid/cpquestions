/*
 * File: 463A.c
 * Author: vididvidid 
 * Created: 2026-07-17 11:24:58
 */

/*
 * s dollar for sugar
 * n types of sugar in market
 * may be he by one. 
 * instead of cents -> give sweets (don't exceed 99)
 * sugar costs x dollar + y cents
 */

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct
{
    int x;
    int y;
} price;

void solve()
{
    int n, s;
    scanf("%d %d", &n, &s);
    price price[n];
    int ans = -1;
    int mp = INT_MAX, idx = -1;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &price[i].x, &price[i].y);
        int lmp = MIN(mp, price[i].x);
        if (lmp != mp || (price[idx].y > price[i].y && lmp == mp))
        {
            idx = i;
            mp = lmp;
        }
    }

    if (mp > s)
    {
        printf("-1\n");
        return;
    }

    if (mp == s){
        if (price[idx].y == 0)
        {
            printf("0\n");
            return;
        }
        printf("-1\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (price[i].x < s)
        {
           
            int k = 100 - price[i].y;
            if (price[i].y == 0) k = 0;
            ans = MAX(ans, k);
        }
    }

    printf("%d\n",ans);
    
}

int main()
{
    solve();
    return 0;
}
