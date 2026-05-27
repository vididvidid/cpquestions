/*
 * File: 1798B.c
 * Author: vididvidid 
 * Created: 2026-05-20 01:33:39
 */

/*
 * find unique number for each sequence..
 *
 *      1    2   3   4   5   6   7   8   9
 * D1:  1    1   0   1   0   0   0   1   0 => 8
 * D2:  2    2   0   1   0   0   0   0   1 => 9
 * D3:  3    2   0   2   0   0   0   1   1 => 1
 *
 * 2d matrix
 * 0    1   2   3   4   5   6   7   8 .... 50,000
 * 1    1   2   4   8   0   0   0   0 ...
 * 2    2   9   1   0   0   0   0   0 ...
 * 3    1   4   0   0   0   0   0   0 ...
 *
 * now global one..
 * freq array.. 
 * 0    1   2   3   4   5   6   7   8
 * 0    3   2   0   2   0   0   0   1
 *
 * --------------------------------------------------------------
 *      1    2
 * D1:  1    1 
 * D2:  2    2  => no winner, winner participated in second
 *
 *      1   2   3   4
 * D1:  1   1   1   1 => 2 
 * D2:  2   1   1   1 => 1
 * D3:  2   1   1   2 => 4
 * D4:  2   1   2   2 => 3 
 *
 * facts:
 * for 1st at the end we should have one number that have freq 1..
 * for every n we have to check from 1 .. n freq.. 2 -> {1, 2} 
 * 2d matrix and a final matrix.. 
 * i need matrix because for that day i need to remember which number appeared
 * i need freq because i need to check if that number occured this many times
 * 
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);

    int all[50005];
    int day[50005];
    int lot[50005];

    int ptr = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%d",&lot[i]);
        day[i] = ptr;

        for (int j = 0; j < lot[i]; j++)
        {
            scanf("%d",&all[ptr]);
            ptr++;
        }
    }

    int seen[50005] = {0};
    int winners[50005] = {0};

    for (int i = n - 1; i >= 0; i--)
    {
        int winner = -1;
        int start_idx = day[i];
        int size = lot[i];

        for (int j = 0; j < size; j++)
        {
            int p = all[start_idx + j];
            if (seen[p] == 0 && winner == -1)  {
                winner = p;
            }
        }


        if (winner == -1)
        {
            printf("-1\n");
            return;
        }

        winners[i] = winner;

        for (int j = 0; j < size; j++)
        {
            int p = all[start_idx + j];
            seen[p] = 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ",winners[i]);
    }
    printf("\n");
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
