/*
 * File: 2227D.c
 * Author: vididvidid 
 * Created: 2026-07-10 18:37:15
 */

/*
 * return max mex value by selecting optimal subarray that is pallindrome.
 *
 * go with O(n) because n is 10^5
 * so in one go find all palindrome, and mex also.
 *
 * because i have to find mex 
 * so i do need to care that i have 0 in that 1 in that.. 
 * things like that.. because if i don't have 0 in the pallindrome that means
 * 0 will be the mex and it can be wrong. 
 *
 * so start by finding the pallindrome that contains 0 and extend left and right 
 * from that point
 *
 * i wasn't able to figure it out how to do it in one loop
 * but reading the editorial got me one thing.. "twice" word is important :-D
 *
 * so question is to locate the position of 0 and try 3 combinations..
 * left - left, left - right, and right-right
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int key;
    int occupied;
} SetItem;

typedef struct {
    SetItem *items;
    size_t count;
    size_t capacity;
} IntSet;

void set_insert(IntSet *s, int key);

void set_realloc(IntSet *s, size_t new_cap) {
    SetItem *old_items = s->items;
    size_t old_cap = s->capacity;

    s->items = calloc(new_cap, sizeof(SetItem));
    s->capacity = new_cap;
    s->count = 0;

    for (size_t i = 0; i < old_cap; i++) {
        if (old_items[i].occupied) {
            set_insert(s, old_items[i].key);
        }
    }
    free(old_items);
}

void set_insert(IntSet *s, int key) {
    if (s->capacity == 0) {
        set_realloc(s, 128);
    } else if (s->count * 2 >= s->capacity) { 
        set_realloc(s, s->capacity * 2);
    }

    size_t index = ((uint32_t)key * 0x45d9f3b) % s->capacity;

    while (s->items[index].occupied) {
        if (s->items[index].key == key) {
            return;
        }
        index = (index + 1) % s->capacity;
    }

    s->items[index].key = key;
    s->items[index].occupied = 1;
    s->count++;
}

int set_contains(IntSet *s, int key) {
    if (s->capacity == 0) return 0;

    size_t index = ((uint32_t)key * 0x45d9f3b) % s->capacity;

    while (s->items[index].occupied) {
        if (s->items[index].key == key) {
            return 1;
        }
        index = (index + 1) % s->capacity;
    }
    
    return 0;
}

void set_free(IntSet *s) {
    free(s->items);
    s->items = NULL;
    s->count = s->capacity = 0;
}

typedef struct {
    int *items;
    size_t qnt;
    size_t space;
} IGnd;

void ignd_push(IGnd *ig, int item) {
    if (ig->qnt >= ig->space) {
        ig->space = (ig->space == 0) ? 128 : ig->space * 2;
        ig->items = realloc(ig->items, ig->space * sizeof(int));
    }
    ig->items[ig->qnt++] = item;
}

void ignd_free(IGnd *ig) {
    if (ig->items) free(ig->items);
    ig->items = NULL;
    ig->qnt = ig->space = 0;
}

typedef struct {
    IGnd *items;
    size_t qnt;
    size_t space;
} IGnd2;

void ignd2_push(IGnd2 *ig, IGnd item) {
    if (ig->qnt >= ig->space) {
        ig->space = (ig->space == 0) ? 128 : ig->space * 2;
        ig->items = realloc(ig->items, ig->space * sizeof(IGnd));
    }
    ig->items[ig->qnt++] = item;
}

void solve() {
    int original_n;
    if (scanf("%d", &original_n) != 1) return;
    
    int n = original_n * 2;

    IGnd arr = {0};
    IGnd2 loc = {0};

    for (int i = 0; i <= original_n; i++) {
        IGnd empty_vec = {0};
        ignd2_push(&loc, empty_vec);
    }

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        
        ignd_push(&arr, x);
        ignd_push(&loc.items[x], i);
    }

    if (loc.items[0].qnt < 2) {
        printf("0\n");
        goto cleanup;
    }

    int p1 = loc.items[0].items[0];
    int p2 = loc.items[0].items[1];
    
    int cands[3] = { p1 + p2, p1 + p1, p2 + p2 };
    int ans = 0;

    for (int i = 0; i < 3; i++) {
        int c = cands[i];
        IntSet cur = {0};

        for (int a = c / 2; a < n && c - a >= 0; a++) {
            if (arr.items[a] != arr.items[c - a]) {
                break;
            }
            
            set_insert(&cur, arr.items[a]);
            set_insert(&cur, arr.items[c - a]);
        }

        int mex = 0;
        while (set_contains(&cur, mex)) {
            mex++;
        }
        
        ans = MAX(ans, mex);
        
        set_free(&cur);
    }

    printf("%d\n", ans);

cleanup:
    for (size_t i = 0; i < loc.qnt; i++) {
        ignd_free(&loc.items[i]);
    }
    free(loc.items);
    ignd_free(&arr);
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
