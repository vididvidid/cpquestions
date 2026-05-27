/*
 * File: 734B.c
 * Author: vididvidid 
 * Created: 2026-04-20 03:39:26
 */

/*
 * there are
 * => k2 digits of 2
 * => k3 digits of 3
 * => k5 digits of 5
 * => k6 digits of 6
 *
 * we have to make max sum of 32 + 256 from that..
 * so min(k2,k5,k6) will give me how many 256 we can make.. 
 * so sum = min * 256 and k2-min, k5-min, k6-min..
 *
 * than min(k2,k3) will give me how many 32 we can make
 * so sum += min * 32 and k2-min, k3-min..
 *
 */
#include <stdio.h>

#define MIN(a,b) (a)<(b) ? (a) : (b)

int main()
{
    int k2,k3,k5,k6;
    scanf("%d %d %d %d",&k2, &k3, &k5, &k6);
    int sum = 0;
    int m1 = MIN(k2, MIN(k5, k6));
    sum = m1 * 256;
    k2 -= m1;
    k5 -= m1;
    k6 -= m1;

    int m2 = MIN(k3, k2);
    sum += m2 * 32;
    
    printf("%d\n",sum);
    return 0;

}
