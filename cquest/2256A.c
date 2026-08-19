/*
 * File: 2256A.c
 * Author: vididvidid 
 * Created: 2026-08-19 22:01:47
 */

#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        long long a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);

        if (a > b) {
            long long x = a;
            a = b;
            b = x;
        }
        if (b > c) {
            long long x = b;
            b = c;
            c = x;
        }
        if (a > b) {
            long long x = a;
            a = b;
            b = x;
        }

        printf("%lld\n", b < c - a ? b : c - a);
    }

    return 0;
}
