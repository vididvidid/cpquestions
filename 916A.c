/*
 * File: 916A.c
 * Author: vididvidid 
 * Created: 2026-05-12 08:50:44
 */

/*
 * time must have digit '7' and after every x minumtes he could reach
 * destination time.. tell the number of steps will occur.. 
 *
 * 00 <= hh <= 23, 00 <= mm <= 59
 *
 * as mm reaches 59 it starts from 00 and hh gets increment by 1 if it reaches
 * 23 than it starts from 0..
 *
 * 1:07 -> 1:02 -> 00:58 -> 00:53 -> 00:48 -> 00:43 -> 00:38 -> 00:33 -> 00:28
 *
 * 00:23 -> 00:18 -> 00:13 -> 00:08 -> 00:03 -> 23:58 
 *
 */
#include <stdio.h>

int main()
{
    int x,hh,mm;
    scanf("%d %d %d",&x, &hh, &mm);

    int cnt = 0;
    int thh = hh, tmm = mm;
    do  {
            int testm = tmm, testh = thh;
            if (testm % 10 == 7) break;
            testm /= 10;
            if (testm % 10 == 7) break;
            if (testh % 10 == 7 ) break;
            testh /= 10;
            if (testh % 10 == 7) break;

        int t = x;
        while (t--)
        {
            if (tmm == 0)
            {
                tmm = 59;
                if (thh == 0) thh = 23;
                else thh -= 1;
            }
            else 
            {
                tmm--;
            }
            /* printf("%d:%d \t",thh,tmm); */
        }
        cnt++;
    } while (thh != hh || tmm != mm);
    if (thh == hh && tmm == mm) cnt = 0;
    /* printf("\n"); */
    printf("%d\n",cnt);
    return 0;
}
