/*
 * File: 1775A1.c
 * Author: vididvidid 
 * Created: 2026-04-23 05:54:20
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    char a[101],b1[101],b2[101],c[101];
    scanf("%s",b1);
    int n = 0;
    for (char *i = b1; *i != '\0'; i++)
    {
        b2[n++] = *i;
    }
    b2[n] = '\0';
    int aps = 0, bps1 = 1, bpe1 = n-2, bps2 = 1, bpe2 = n-2, cps = n-1;
    a[0] = b1[0];
    a[1] = '\0';
    c[n] = '\0';
    c[n-1] = b1[n-1];
    b1[n-1] = '\0';
    b2[n-1] = '\0';
    int flag1 = 0, flag2 = 0;
    /* while (bps1 < bpe1) */
    /* { */
       /* printf("DEBUG: aps: %d bps1: %d bpe1: %d cps: %d\n",aps,bps1,bpe1,cps); */
       /* printf("DEBUG: a: %s, b1: %s, c: %s\n",a,&b1[bps1],&c[cps]); */
       while (bps1 < bpe1 && aps < n-1 && cps > 0 )
       {
           if (strcmp(a,&b1[bps1])<=0 && strcmp(&c[cps],&b1[bps1])<=0) 
           {
               flag1 = 1;
               break;
           }
           if (strcmp(a,&b1[bps1]) > 0)
           {
               a[++aps] = b1[bps1++];
               a[aps+1] = '\0';
               /* printf("DEBUG:\n\ta: %s, b: %s\n",a,&b1[bps1]); */ 
           } 
           else if (strcmp(&c[cps],&b1[bps1]) > 0)
           {
                c[--cps] = b1[bpe1];
                b1[bpe1--] = '\0';
                /* printf("DEBUG:\n\tc: %s, b: %s\n",&c[cps],&b1[bps1]); */ 
           }
           /* */
       }

       /* while (!flag1 && bps1 < bpe1 && cps > 0 && */ 
       /* { */
       /*     if (strcmp(a,&b1[bps1])<=0 && strcmp(&c[cps],&b1[bps1])<=0) */ 
       /*     { */
       /*         flag1 = 1; */
       /*         break; */
       /*     } */
       /*     /1* *1/ */
       /* } */
    /* } */
       if (strcmp(a,&b1[bps1])<=0 && strcmp(&c[cps],&b1[bps1])<=0) 
       {

           /* printf("INSIDE: a: %s b: %s c: %s\n",a,&b1[bps1],&c[cps]); */
           flag1 = 1;
       }

     /* printf("BDEBUG:a: %s c: %s, b: %s\n",a,&c[cps],&b1[bps1]); */

     if (!flag1)
     {
       aps = 0, cps = n-1;
       a[1] = '\0';

       /* printf("FLAG1\n"); */
       /* printf("DEBUG: aps: %d bps1: %d bpe1: %d cps: %d\n",aps,bps2,bpe2,cps); */
       /* printf("DEBUG: a: %s, b2: %s, c: %s\n",a,&b2[bps2],&c[cps]); */
       while (bps2 < bpe2 && aps < n-1 &&  cps > 0)
       {
           if (strcmp(a,&b2[bps2])>=0 && strcmp(&c[cps],&b2[bps2])>=0) 
           {
               flag2 = 1;
               break;
           }
           if (strcmp(a,b2 + bps2) < 0)
           {
            a[++aps] = b2[bps2++];
            a[aps+1] = '\0';
            /* printf("DEBUG:\n\ta: %s, b: %s\n",a,&b2[bps2]); */ 
           }
           else if (strcmp(c+cps,b2+bps2) < 0)
           {
            c[--cps] = b2[bpe2];
            b2[bpe2--] = '\0';
            /* printf("DEBUG:\n\tc: %s, b: %s\n",&c[cps],&b2[bps2]); */ 
           }
           /* */
       }

       /* while (!flag2 && bps2 < bpe2 && cps > 0 && strcmp(c+cps,b2+bps2) > 0) */
       /* { */
           
       /*     if (strcmp(a,&b2[bps2])>=0 && strcmp(&c[cps],&b2[bps2])>=0) */ 
       /*     { */
       /*         flag2 = 1; */
       /*         break; */
       /*     } */
       /*     /1* *1/ */
       /* } */
    }

    if (flag1)
    {
        printf("%s %s %s\n",a,b1+bps1,c+cps);
    } else 
    {
        printf("%s %s %s\n",a,b2+bps2,c+cps);
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
