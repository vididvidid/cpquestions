/*
 * File: 1207A.c
 * Author: vididvidid 
 * Created: 2026-04-26 02:29:13
 */

/*
 * check if h > c 
 * than check if we have that much buns.. 
 *
 * if (price(ham) > price(chick)) :
 *      => if (buns)
 *      =>  sum = min(ham*2,buns) * price
 *      =>  buns -= min(ham*2,buns);
 *      =>  if (buns):
 *          => sum += min(chick *2 , buns) *price
 *          => buns -= min(chick * 2, buns);
 * else :
 *      if (buns)
 *      => sum = min(chick * 2, buns) * price
 *      => buns -= min(chick * 2, buns);
 *      => if (buns) :
 *          => sum += min(ham * 2, buns) * price
 *          => buns -= min()
 *
 *  15 2 3 5 10
 *
 *  if (buns): // 15 -> TRUE
 *      => sum += MIN(3 * 2 , 15)/2 * price // 6/2 * 10 = 30
 *      => buns -= MIN(3*2, 15)             // buns = 9
 *      => if (9):                          // TRUE
 *          => sum += MIN(2 * 2, 9)/2 * 2   // 4/ 2 * 5 = 10 => 30 + 10 = 40
 *          => buns -= MIN(2*2,9)/2 * 2     // buns = 5
 * 
 *
 * 7 5 2 10 12
 *
 * if (buns) :                              // TRUE
 *      => sum += MIN(2*2,7)/2 * 12         // 4/2 * 12 = 24
 *      => buns -= MIN(2*2,7);              // buns = 3
 *      => if (buns)                        // TRUE
 *          => sum += MIN(5 * 2, 3)/2 * 10  // 3/2 * 10 = 10 => 24 + 10 = 34
 *          => buns -= MIN(5*2, 3)/2 * 2    // buns = 1;
 *
 */
#include <stdio.h>

#define MIN(a,b) (a)<(b)?(a):(b)

void solve()
{
    int buns,ham,chick,pham,pchick;
    scanf("%d %d %d %d %d",&buns,&ham,&chick,&pham,&pchick);
    int sum = 0;
    if (pham > pchick)
    {
        sum += ((MIN(ham * 2, buns))/2) * pham;
        buns -= ((MIN(ham*2, buns))/2) * 2;
        if (buns) 
        {
            sum += ((MIN(chick * 2, buns))/2) * pchick;
            buns -= ((MIN(chick * 2, buns))/2 ) * 2;
        }
    }
    else
    {
        sum += ((MIN(chick * 2, buns))/2) * pchick;
        buns -=( ((MIN(chick *2, buns))/2) *2);
        if (buns)
        {
            sum += ((MIN(ham * 2, buns))/2) *pham;
            buns -= ((MIN(ham*2, buns))/2) * 2;
        }
    }

    printf("%d\n",sum);
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
