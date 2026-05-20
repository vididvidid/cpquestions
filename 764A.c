/*
 * File: 764A.c
 * Author: vididvidid 
 * Created: 2026-04-27 07:40:42
 */

/* find how many occurenecs of n and m are tere till z.
 */

#include <stdio.h>

int main()
{
    int n,m,z;
    scanf("%d %d %d",&n, &m, &z);
    int ans =0;
    int k = 1, l = 1;
    for (int i = 1; i <= z; i++)
    {
        /* printf("%d [ ",i); */
        int a = k*n;
        int b = l*m;
        /* printf(" --%d %d-- ",a,b); */
        if (a == b && a == i){
            /* printf("* "); */
            ans++;
        }
        if (i == a){
            /* printf("c "); */
            k++;
        }
        if (i == b) {
            /* printf("a "); */
            l++;
        }
       /* printf("] "); */ 
    }
    /* printf("\n"); */
    printf("%d\n",ans);
    return 0;
}
