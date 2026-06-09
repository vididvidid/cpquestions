/*
 * File: gnd.c
 * Author: vididvidid 
 * Created: 2026-06-09 15:25:43
 */


#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "ds/GND.h" 
typedef struct {
    int u, v, weight;
} Edge;

void solve() {
    gnd(int) arr = {0};
    gnd(Edge) edges = {0};

    for (int i = 0; i < 5; i++) {
        push(arr, i * 10);
    }

    Edge e1 = {1, 2, 15};
    push(edges, e1);

    for (size_t i = 0; i < arr.count; i++) {
        printf("%d ", arr.items[i]);
    }
    printf("\n");

    int last_val = pull(arr);
    printf("pullped: %d\n", last_val);

    free_gnd(arr);
    free_gnd(edges);
}

int main() {
    solve();
    return 0;
}
