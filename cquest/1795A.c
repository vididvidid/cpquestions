/*
 * File: 1795A.c
 * Author: vididvidid 
 * Created: 2026-04-23 02:57:12
 */

/*
 * check if the string is or can be formed to make a alterate pattern or not.
 * BRBR or RBRB..
 * B->66 and R->(82)
 * so 66-82 or 82-66
 * (66+82)%148 = 0      (66+66)%148 = 132   (82+82)%148 = 16
 *
 * so first check if both the string are beautiful or not.. 
 * which means the sum will be 0 at the end.. 
 *
 * fucntion to check if it is beautiful or not
 * and one go from first to second.. 
 * than go from second to first..
 * if in any of the condition we get the flag = 1 than just print yes..
 */

#include <stdio.h>
#include <string.h>

int check (char *arr, char *brr)
{
    char *tmp = arr;
    for (char *i = tmp+1; *i != '\0'; i++)
    {
        if (*i == *(i-1)){
            return 0;
        }
    }
    tmp = brr;
    for (char *i = tmp+1; *i != '\0'; i++)
    {
        if (*i == *(i - 1)) return 0;
    }
    return 1;
}

void solve()
{
    int n,m;
    scanf("%d %d",&n,&m);
    char arr[n+m],brr[m+n];
    scanf("%s %s",arr, brr);
    int flag = 0;
    flag = check(arr,brr);
    if (!flag)
    {
        int t = n, k = m-1;
        char  nrr[n+m], mrr[n+m];
        strcpy(nrr,arr);
        strcpy(mrr,brr);
        /* printf("\t%s\n\t%s\n",nrr,mrr); */
        while (!flag && t >= 0 && k >= 0)
        {
           /* printf("\tt:%d k:%d nrr[t]:%c mrr[k]:%c\n",t,k,(char)nrr[t],(char)mrr[k]); */
           nrr[t++] = mrr[k--];
           nrr[t] = '\0';
           mrr[k+1] = '\0';
           /* printf("\tt:%d k:%d nrr[t]:%c mrr[k]:%c\n",t,k,(char)nrr[t-1],(char)mrr[k]); */
           flag = check(nrr,mrr);
           /* printf("%s\t|\t%s\n",nrr,mrr); */
           /* printf("--------------------------------------------------\n"); */
        }
    }        
    if (!flag)
    {
        int t = n-1, k = m;
        char nrr[n+m], mrr[n+m];
        strcpy(nrr,arr);
        strcpy(mrr,brr);
        /* printf("\tOrg\n\t%s\t|\t%s\n",nrr,mrr); */
        while (!flag && t>=0 && k>=0)
        {
            mrr[k++] = nrr[t--];
            mrr[k] = '\0';
            nrr[t+1] = '\0';
            /* printf("\t%s\t|\t%s\n",nrr,mrr); */
            flag = check(nrr,mrr);
            /* printf("------------------------------------------------\n"); */
        }
    }

    if (flag)
    {
        printf("YES\n");
    } else
    {
        printf("NO\n");
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
