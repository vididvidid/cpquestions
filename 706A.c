/*
 * File: 706A.c
 * Author: vididvidid 
 * Created: 2026-05-13 05:31:34
 */

#include <stdio.h>
#include <math.h>

#define MIN(a,b) (a)<(b)?(a):(b)
#define ABS(a) (a)<0?-1*(a):(a)

int main()
{
    double a,b;
    scanf("%lf %lf",&a,&b);
    int n;
    scanf("%d",&n);
    double ans = 1e18;
    while (n--)
    {
        double tx, ty, tv;
        scanf("%lf %lf %lf",&tx, &ty, &tv);
        double tans = (sqrt(pow(ABS(tx-a),2) + pow(ABS(ty-b), 2)))/tv;
        ans = MIN(ans, tans);
    }
    printf("%.20f\n",ans);
    return 0;
}

