/*
 * File: 9B.c
 * Author: vididvidid 
 * Created: 2026-07-18 12:05:37
 */

/*
 * start (0,0) -> got on minibus -> along straight line -> parallel to OX -> in
 * direction of increasing x
 * -> one run -> minibus -> n stops -> ith stop is (xi, 0)
 * -> coordinate of all stops different
 * -> minibus -> constant speed -> equal to vb
 * -> get off from bus -> only at stops
 * -> if don't get off earlier -> get off at terminal stop
 * -> univeristy exam held -> xu, yu
 * -> student -> run -> bus stop -> uni -> vs 
 * -> student already at minibus, can't get out at first stop
 *
 *  speed = distance / time = > 
 *  time = distance / speed
 *  distance = sqrt((x2 - x1)^2 - (y2 - y1)^2)
 *  
 *  time in bus + time walking to uni
 *
 */
#include <stdio.h>
#include <math.h>


void solve()
{
    int n, vb, vs;
    scanf("%d %d %d", &n, &vb, &vs);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int xu, yu;
    scanf("%d %d", &xu, &yu);
   
    double min_time = 1e18;
    double min_dist = 1e18;
    int best_stop = 2;

    for (int i = 1; i < n; i++)
    {
        double tb = (double)arr[i] / vb;
        double dx = (double)(xu - arr[i]);
        double dy = (double)yu;
        double du = sqrt(dx * dx + dy * dy);
        double tu = du / vs;
        double ts = tb + tu;

        if (ts < min_time - 1e-9)
        {
            min_time = ts;
            min_dist = du;
            best_stop = i + 1;
        }
        else if (fabs(ts - min_time) <= 1e-9)
        {
            if (du < min_dist - 1e-9)
            {
                min_dist = du;
                best_stop = i + 1;
            }
        }
    }

    printf("%d\n",best_stop);
}

int main()
{
    solve();
    return 0;
}
