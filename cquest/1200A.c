/*
 * File: 1200A.c
 * Author: vididvidid 
 * Created: 2026-04-26 03:00:33
 */

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    scanf("%d",&n);
    int arr[10] = {0};
    char lst[n+1];
    int l = 0, r = 9;
    scanf("%s",lst);
    int idx = 0;
    while (lst[idx]!='\0')
    {
       if (lst[idx] == 'L')
       {
           while (l < 10 && arr[l] == 1) l++;
           arr[l] = 1;
           while (l < 10 && arr[l] == 1) l++;
       } else if (lst[idx] == 'R')
       {
           while (r >= 0 && arr[r] == 1) r--;
           arr[r] = 1;
           while (r >= 0 && arr[r] == 1) r--;
       } else 
       {
           int k = lst[idx] - '0';
           if (k < l) l = k;
           if (k > r) r = k;
           arr[k] = 0;
       }
       idx++;
       /* for (int i = 0; i < 10; i++) */
       /*     printf("%d",arr[i]); */
       /* printf("\n"); */
    }
    for (int i = 0; i < 10; i++)
        printf("%d",arr[i]);

    printf("\n");
    return 0;
}
