/*
 * File: 1011B.c
 * Author: vididvidid 
 * Created: 2026-07-16 23:20:30
 */

/*
 * n people
 * m daily food package -> ai food type
 * each participant -> one food package -> each day -> same food eat
 * different participant may eat different(same ) type of food
 * find how many days can eat same food.. 
 * 
 * n < m -> 0
 * n == m -> 1
 * n > m :
 * 
 */

#include <stdio.h>

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int count[101] = {0};
    for (int i = 0; i < m; i++)
    {
        int t;
        scanf("%d", &t);
        count[t]++;
    }

    for (int d = m; d >= 1; d--)
    {
        int eat = 0;

        for (int t = 1; t <= 100; t++)
        {
            eat += count[t]/d;
        }

        if (eat >= n)
        {
            printf("%d\n",d);
            return;
        }
    }

    printf("0\n");
}

int main()
{
    solve();
    return 0;

}
