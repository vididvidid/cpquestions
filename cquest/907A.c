/*
 * File: 907A.c
 * Author: vididvidid 
 * Created: 2026-11-03 07:01:20
 */

#include <stdio.h>

void solve()
{
    int fb, mb, sb ,masha;
    scanf("%d %d %d %d", &fb, &mb, &sb, &masha);

    int carfb = -1, carmb = -1, carsb = -1;

    for (int i = sb; i <= (2 * sb); i++)
    {
        if (i >= masha && i <= (2 * masha))
        {
           carsb = i;
           break;
        }
    }

    for (int i = mb; i <= (2 * mb); i++)
    {
        if (carsb < i && sb < i && (2*sb) < i && i > (2 * masha))
        {
            carmb = i;
            break;
        }
    }

    for (int i = fb; i <= (2 * fb); i++)
    {
        if (carmb < i && mb < i && (2*mb) < i && i > (2 * masha))
        {
            carfb = i;
            break;
        }
    }

    if (carsb == -1 || carmb == -1 || carfb == -1)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n%d\n%d\n",carfb,carmb,carsb);
    }
}

int main()
{
    solve();
    return 0;
}
