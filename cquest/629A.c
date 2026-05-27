/*
 * File: 629A.c
 * Author: vididvidid 
 * Created: 2026-05-06 04:30:45
 */

/*
 * calculate the nC2 row wise and col wise... and return the sum..
 *
 */

#include <stdio.h>

#define int long long
#define ABS(a) (a)<0?-1*(a):(a)

int fact(int n)
{
    int ans = 1; 
    for (int i = 1; i <= n; i++)
    {
        ans *= i;
    }
    /* printf("Factorial: %llu =>  %llu\n",n, ans); */
    return ans;
}

int com(int n, int m)
{
    /* int num = fact(n); */
    /* printf("DEBUG: n-m : %lld\n",n-m); */
    /* int den2 = fact(ABS(n-m)); */
    int ans = (n * (n - 1)) / (2);
    /* int ans = num / (den1 * den2); */
    /* printf("Comb: %lluC%llu => %llu\n",n,m,ans); */
    return ans;
}

int main()
{
    int n;
    scanf("%lld",&n);
    /* printf("DEBUG : n: %lld\n",n); */
    char s[n][n+1];
    for (int i = 0; i < n; i++)
    {
        scanf("%s",s[i]);
        s[i][n] = '\0';
    }
    /* for (int i = 0; i < n; i++) */
    /* { */
    /*     printf("%s\n",s[i]); */
    /* } */
    int sr = 0, sc = 0;
    for (int i = 0; i < n; i++)
    {
        int tc = 0;
        for (int j = 0; j < n; j++)
        {
            if (s[i][j] == 'C') tc++;
        }
        sr += com(tc,2);
    }
    /* printf("SR: %lld\n",sr); */
    for (int i = 0; i < n; i++)
    {
        int tr = 0;
        for (int j = 0; j < n; j++)
        {
            if (s[j][i] == 'C') tr++;
        }
        sc += com(tr,2);
    }
    /* printf("SC: %lld\n",sc); */
    printf("%lld\n",sr+sc);
    return 0;
}
