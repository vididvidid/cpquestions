/*
 * File: 1313A.c
 * Author: vididvidid 
 * Created: 2026-05-11 07:05:11
 */

/*
 * ABC are the dishes and we have the frequency of ABC tell me how many unique
 * customers we can treat
 *
 * so max we can go is 7.. [A, B, C, AB, AC, BC, ABC]
 *
 * but now the trouble is how to get it with the frequency and give answer
 *
 * so here we use the bitmask to generate all the subsets..
 *
 * 0    =>  000 => {} EMPTY
 * 1    =>  001 => {C}
 * 2    =>  010 => {B}
 * 3    =>  011 => {BC}
 * 4    =>  100 => {A} 
 * 5    =>  101 => {AC}
 * 6    =>  110 => {AB}
 * 7    =>  111 => {ABC}
 *
 * but here comes another part we are given frequency 
 * so if A -> 4 | B -> 4 | C -> 4
 * because in total we have 7 items and we can have any type of combination or
 * precisely saying we have to figure out which combinaton to perfectly fit in
 * to give the unique orders..
 * 000  =>  0000000 =>  {}
 * 001  =>  0000001 =>  {take item 0} => {}
 * 002  =>  0000010 =>  {take item 1} => {C}
 * 003  =>  0000011 =>  {take item 0,1} => {-,C}
 * 004  =>  0000100 =>  {ti: 2} => {B}
 * 005  =>  0000101 =>  {ti: 0,2} => {-,B}
 * 006  =>  0000110 =>  {ti: 1,2} => {C,B}
 * 007  =>  0000111 =>  {ti: 0,1,2} => {-,C,B}
 * 008  =>  0001000 =>  {ti: 3} => {BC}
 * 009  =>  0001001 =>  {ti: 0,3} => {-,BC}
 * 010  =>  0001010 =>  {ti: 1,3} => {C,BC}
 * 011  =>  0001011 =>  {ti: 0,1,3} => {-,C,BC}
 * 012  =>  0001100 =>  {ti: 2,3} => {B,BC}
 * 013  =>  0001101 =>  {ti: 0,2,3} => {-,B,BC}
 * 014  =>  0001110 =>  {ti: 1,2,3} => {C,B,BC}
 * 015  =>  0001111 =>  {ti: 0,1,2,3} => {-,C,B,BC}
 * 016  =>  0010000 =>  {ti: 4} => {A}
 * 017  =>  0010001 =>  {ti: 0,4} => {-,A}
 * ... so similary we can get all the combinations of 7 ways for that ABC
 *
 * so which means 2*2*2*2*2*2*2 = 128 if we want all 7 we need 128
 *
 * for: go with all combinations
 * =>   for: go will all 7 bits in that number
 *      =>  if that index is 1 that means include that in result
 */

#include <stdio.h>

#define MAX(a,b) (a)>(b)?(a):(b)

void solve()
{
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    
    int ans = 0;
    for (int i = 0; i < 128; i++)
    {
        int req1 = 0, req2 = 0, req3 = 0;
        int cur = 0;

        for (int bit = 0; bit < 7; bit++)
        {
            if ((i & (1 << bit)) != 0)
            {
                int item = bit+1;
                if (item & 1) req1++;
                if (item & 2) req2++;
                if (item & 4) req3++;
                cur++;
            }
        }
        /* printf("DEBUG: %d\n",cur); */
        if (req1 <= a && req2 <= b && req3 <= c)
        {
            ans = MAX(ans,cur);
        }
    }

    printf("%d\n",ans);
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
