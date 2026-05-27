/*
 * File: 1005B.c
 * Author: vididvidid 
 * Created: 2026-05-12 03:49:23
 */

/*
 * tell the max common prefix.. in the string..
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 200001

int main()
{
    char a[MAXLEN], b[MAXLEN];
    scanf("%s %s",a,b);
    int n, m;
    n = strlen(a);
    m = strlen(b);
    int t = n, q = m;
    n--;m--;
    while (n >= 0 && m >= 0)
    {
        if (a[n] != b[m])
        {
            /* printf("DEBUG: break %c %c and %d %d\n",a[n],b[m],n,m); */
            break;
        }
        n--;m--;
    }
    /* printf("n %d and %d\n", n+1, t-n+1); */
    /* printf("m %d and %d\n", m+1, q-m+1); */
    printf("%d\n",(n+m+2));
    return 0;
}
