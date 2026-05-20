/*
 * File: 811A.c
 * Author: vididvidid 
 * Created: 2026-04-28 13:21:23
 */

/*
 * a gives x candies to b   than
 * b gives x+1 candies to a than
 * a gives x+2 candies to b ... game goes on
 *
 * we have to tell in a,b which will be the first who will not be able to 
 * give his own candies..
 *
 * demand = 1
 * while (a > demand && b > deman) :
 *  if (i % 2 == 0) a--;
 *  else b--;
 *  demand++;
 */

#include <stdio.h>

int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    int demand = 1,count =0;
    int flag = 0;
    while (1)
    {
        if ( count % 2 == 0 && a < demand) {
            flag = 1;
            break;
        }
        if (count % 2 != 0 && b < demand) {
            flag = 0;
            break;
        }
       if (count % 2 == 0) a-=demand;
       else b-=demand;
       demand++;
       count++;
    }
    if (flag) printf("Vladik\n");
    else printf("Valera\n");
}
