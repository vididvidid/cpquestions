/*
 * File: 1703C.c
 * Author: vididvidid 
 * Created: 2026-04-14 12:23:05
 */

// given digits of the lock.. and each have the movement
// D - move down..  U - move up
// 0 -- 9.. the digits..
//
// can done manually as the b max is 10..
//
#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    int wheel[n];
    for (int i = 0; i < n ; i++) scanf("%d",&wheel[i]);
    
    /* printf("--- DEBUG ----\n"); */
    /* for (int i = 0; i < n; i++) printf("%d ", wheel[i]); */
    /* printf("\n"); */
    


    for (int i = 0; i < n; i++) {
        int b;
        scanf("%d",&b);
        char seq[b];
        scanf("%s",seq);
        int tmp = wheel[i];

        /* printf("b is : %d seq: %s \n",b, seq); */
        


        for (int j = 0; j < b; j++)
        {
            if (seq[j] == 'D'){
                if (tmp == 9) {
                    tmp %= 9;
                } else {
                    tmp++;
                }
            } else {
                /* printf("\t inside up\n"); */
                if (tmp == 0){
                    tmp = 9;
                }  else {
                    --tmp;
                }
            }
            /* printf("\t tmp value is %d\n",tmp); */
        }
    
        wheel[i] = tmp;

    }

    for (int i = 0; i < n ; i++) {
        printf("%d ",wheel[i]);
    }
    printf("\n");
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}
