/*
 * File: 1511C.c
 * Author: vididvidid 
 * Created: 2026-06-22 15:32:39
 */

/*
 * given an array of n numbers (1 <= A[i] <= 50). process Q queries. for each
 * query x, find the minimum index i where A[i] == x. Print i, then execute move
 * to front operation on A[i].
 *
 */

#include <stdio.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n], brr[m], prr[51] = {0};
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
        if (!prr[arr[i]])
            prr[arr[i]] = i;
    }

    /* printf("   : "); */
    /* for (int i = 0; i <= 50; i++) */
    /* { */
    /*     if (prr[i] != 0) */
    /*     printf("%d\t",i); */
    /* } */
    /* printf("\n"); */
    /* for (int i = 0; i <= 50; i++) */
    /* { */
    /*     if (prr[i] != 0) */
    /*     printf("%d\t",prr[i]); */
    /* } */
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &brr[i]);
        printf("%d ",prr[brr[i]]);
        int idx = prr[brr[i]];
        for (int j = 0; j <= 50; j++)
        {
            if (j == brr[i]){
                prr[j] = 1;
            }
            else  if (prr[j] != 0 && prr[j] < idx){
                prr[j]++;
            } 
        }

        // debug
        /* printf("\n%d : ", brr[i]); */
        /* for (int j = 0; j <= 50; j++) */
        /* { */
        /*     if (prr[j] != 0) */ 
        /*         printf("%d\t", prr[j]); */
        /* } */
        /* printf("\n"); */
    }
    printf("\n");
}
