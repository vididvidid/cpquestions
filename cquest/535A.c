/*
 * File: 535A.c
 * Author: vididvidid 
 * Created: 2026-06-06 14:45:03
 */

#include <stdio.h>

int main()
{
    int s;
    scanf("%d",&s);
    const char *ones[] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };

    const char *tens[] = {
        "", "", "twenty", "thirty", "forty",
        "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    if (s <= 19) {
        printf("%s\n",ones[s]);
    } else
    {
        if (s%10 == 0) {
            printf("%s\n",tens[s / 10]);
        } else {
            printf("%s-%s\n",tens[s / 10], ones[s % 10]);
        }
    }

    return 0;
}
