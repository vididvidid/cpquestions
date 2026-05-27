/*
 * File: 931A.c
 * Author: vididvidid 
 * Created: 2026-04-29 09:47:25
 */

#include <stdio.h>

#define ABS(a) (a)<0?-1*(a):(a)

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int val = ABS(n-m);
    /* printf("VAL: %d\n",val); */
    if (val  <= 1) 
    {
        printf("%d\n",val);
        return 0;
    } else 
    {
        if (val%2 ==0 )
        {
            val /= 2;
            int ans = 2 * (val * (val + 1)/2);
            printf("%d\n",ans);
        }
        else 
        {
            val /= 2;
            int ans = ((val * (val + 1))/2);
            val++;
            int fn = ((val * (val + 1))/2);
            /* printf("ANS: %d =>  %d and %d\n",val, ans,fn); */
            printf("%d\n",fn+ans);
        }
    }
    return 0;

}
