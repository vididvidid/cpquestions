/*
 * File: 106B.c
 * Author: vididvidid 
 * Created: 2026-06-08 17:03:14
 */

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int speed;
    int ram;
    int hdd;
    int cost;
    int id;
    bool outdtd;
} Laptop;

int main()
{
    int n;
    scanf("%d", &n);

    Laptop laptops[105];

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d %d", &laptops[i].speed, &laptops[i].ram, &laptops[i].hdd,
                &laptops[i].cost);
        laptops[i].id = i + 1;
        laptops[i].outdtd = false;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (laptops[i].speed < laptops[j].speed &&
                laptops[i].ram < laptops[j].ram &&
                laptops[i].hdd < laptops[j].hdd) {
                laptops[i].outdtd = true;
                break;
            }
        }
    }

    int mncost = 2000;
    int id = -1;
    for (int i = 0; i < n; i++)
    {
        if (!laptops[i].outdtd) {
            if (laptops[i].cost < mncost) {
                mncost = laptops[i].cost;
                id = laptops[i].id;
            }
        }
    }

    printf("%d\n", id);
    return 0;
}
