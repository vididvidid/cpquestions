/*
 * File: 919A.c
 * Author: vididvidid 
 * Created: 2026-04-29 09:14:37
 */

#include <stdio.h>
#include <float.h>

#define MIN(a,b) (a)<(b)?(a):(b)

int main()
{
    double n,m;
    scanf("%lf %lf",&n, &m);
    double ans = FLT_MAX;
    int val = -1;
    for (int i = 0; i < n; i++)
    {
        double a, b;
        scanf("%lf %lf",&a, &b);
        double tmp = a/b;
        /* printf("%lf %lf\n",tmp,ans); */
        if (tmp < ans) {
            ans = tmp;
            val = b;
        }
    }

    printf("%.8f\n",ans*m);
    return 0;
}
