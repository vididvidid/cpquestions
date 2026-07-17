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
    char s[n][1005];
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
        for (int j = 0; j < n; j++)
        {
            int allowed[26] = {0};
            int dc = 0;

            for (int k = 0; k < 26; k++)
            {
                if (arr[i][k] > 0 || arr[j][k] > 0)
                {
                    allowed[k] = 1;
                    dc++;
                }
            }

            if (dc <= 2)
            {
                int sum = 0;
                for (int m = 0; m < n; m++)
                {
                    if (arr[m][26] > 0 && arr[m][26] <= 2)
                    {
                        int valid = 1;
                        for (int k = 0; k < 26; k++)
                        {
                            if (arr[m][k] > 0 && allowed[k] == 0)
                            {
                                valid = 0;
                                break;
                            }
                        }

                        if (valid)
                        {
                            for (int k = 0; k < 26; k++)
                            {
                                sum += arr[m][k];
                            }
                        }
                    }
                }
                ans = MAX(ans, sum);
            }
        }
    }

    printf("%d\n",ans);


}

int main()
{
    solve();
    return 0;
}
