/*
 * File: 593A.c
 * Author: vididvidid 
 * Created: 2026-07-17 08:53:00
 */

/*
 * at most 2 distinct letter
 * words with max 2 distinct only.. or combination
 *
 */

#include <stdio.h>
#include <string.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

void solve()
{
    int n;
    scanf("%d", &n);
    char s[n][101];
    int arr[n][27], freq[26] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            arr[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%s", s[i]);
        int val = 0;
        for (int j = 0; j < strlen(s[i]); j++)
        {
            if (arr[i][s[i][j]-'a'] == 0)
            {
                val++;
            }
            arr[i][s[i][j]-'a']++;
        }
        arr[i][26] = val;
    }


    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int freq[26] = {0};
        if (arr[i][26] > 0 && arr[i][26] < 3)
        {
            for (int j = 0; j < 26; j++)
            {
                freq[j] = arr[i][j];
            }

            for ( int j = 0; j < n; j++)
            {
                if (j != i && arr[j][26] > 0 && arr[j][26] < 3)
                {

                    int ck = 0;
                    for (int k = 0; k < 26; k++)
                    {
                        if (freq[k] > 0 || arr[j][k] > 0)
                        {
                            ck++;
                        }
                    }
                    if (ck <= 2)
                    {

                        for (int k = 0; k < 26; k++)
                        {
                            freq[k] += arr[j][k];
                        }
                    }
                }
            }

            int sum = 0;
            for (int j = 0; j < 26; j++)
            {
                sum += freq[j];
            }
            ans = MAX(ans, sum);
        }
    }


    printf("%d\n",ans);


}

int main()
{
    solve();
    return 0;
}
