/*
 * File: 732A.c
 * Author: vididvidid 
 * Created: 2026-04-11 13:31:12
 */

// shovel -> k rupees
// unlimited 10 rupees and r rupees (only one)
// so we have to tell how many shovel he can buy
// k rupees -> 1 shovel
// so if last digit of k and then check if it needed change or not..
// if lk == r than 1.. else .. do the loop from 1 to 9 and check if the lk == k
// else 10.. will be answer.. 
#include <stdio.h>

int main()
{

    int k, r;
    scanf("%d %d",&k, &r);
    int lk = k%10;
    if (lk == r || lk == 0) {
        printf("1\n");
    } else if (lk == 5) {
        printf("2\n");
    } else {
        int res = 0;
        for (int i = 1; i <= 9; i++){
            int temp = (lk *i)%10;
            if (temp == r){
                res = i;
                break;
            }
        }
        if (res == 0) {
            for (int i = 1; i <=9; i++){
                int temp = lk *i;
                if (temp % 10 == 0){
                    res = i;
                    break;
                }
            }
        }
        printf("%d\n",res);
    }
    return 0;
}
