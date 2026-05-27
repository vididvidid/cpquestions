/*
 * File: 551A.c
 * Author: vididvidid 
 * Created: 2026-04-27 03:53:04
 */

/*
 * array to string and store it..
 * each index of array corresponds to strting[index][collection];
 */
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    scanf("%d",&n);
    int **arr = calloc(2001, sizeof(int *));
    for (int i = 0; i < 2001; i++) {
        arr[i] = calloc(2001, sizeof(int));
    }
    for (int i = 0; i < n; i++) {
       int t;
       scanf("%d",&t);
       arr[t][0]++;
       arr[t][arr[t][0]] = i;
    }
    /* for (int i = 0; i < 4; i++) */
    /* { */
    /*     for (int j = 0; j < arr[i][0]; j++) */
    /*     { */
    /*         printf("%d ",arr[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    /* printf("\n"); */



    int srr[n];
    for (int i = 0; i < n; i++) srr[i] = 0;


    int count = 2000,rank = 1 ;
    while (count > 0)
    {
        while (count > 0 && arr[count][0] == 0) count--;
        int inc = 0;
        while (arr[count][0]!=0){
            /* int test = arr[count][arr[count][0]]; */
            /* printf("\tTEST: %d\n",test); */
            srr[ arr[count][arr[count][0]] ] = rank;
            arr[count][0]--;
            inc++;
        }
        rank += inc;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ",srr[i]);
    }
    printf("\n");


    for (int i = 0; i < 2001; i++) free(arr[i]);
    free(arr);
    return 0;
}
