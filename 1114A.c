/*
 * File: 1114A.c
 * Author: vididvidid 
 * Created: 2026-04-26 06:07:49
 */

#include <stdio.h>

#define int long long
signed  main()
{
    int a,b,c,p,q,r;
    scanf("%lld %lld %lld %lld %lld %lld",&a, &b, &c,&p, &q, &r);
    if (p < a) {
        printf("NO\n");
        return 0;
    }
    else p -= a;
    if ((p+q) < b){
        printf("NO\n");
        return 0;
    } 
    int sum = p + q + r;
    sum -= b;
    /* printf("%lld\n",sum); */
    if (sum < c) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    return 0;
}
