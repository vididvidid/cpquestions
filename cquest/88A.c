/*
 * File: 88A.c
 * Author: vididvidid 
 * Created: 2026-07-17 19:18:18
 */

/*
 * 12 notes: C, C#, D, D#, E, F, F#, G, G#, A, B, H
 * distance between C and E is 4 and E and C is 8 semitone
 * chord : unordered set -> three notes -> triads
 * triads -> minor or major 
 * major triad -> X Y Z -> distance b/w X and Y = 4 -> Y and Z => 3 -> X Z = 7
 * minor triad -> XY = 3 -> YZ = 4
 */

#include <stdio.h>
#include <string.h>

typedef struct
{
    char x;
    char sy;
    int freq;
} Notes;

Notes note[12];

void solve()
{
    memset(note, 0, sizeof(note));
    note[0].x = 'C'; note[0].sy = ' '; note[0].freq = 0;
    note[1].x = 'C'; note[1].sy = '#'; note[1].freq = 0;
    note[2].x = 'D'; note[2].sy = ' '; note[2].freq = 0;
    note[3].x = 'D'; note[3].sy = '#'; note[3].freq = 0;
    note[4].x = 'E'; note[4].sy = ' '; note[4].freq = 0;
    note[5].x = 'F'; note[5].sy = ' '; note[5].freq = 0;
    note[6].x = 'F'; note[6].sy = '#'; note[6].freq = 0;
    note[7].x = 'G'; note[7].sy = ' '; note[7].freq = 0;
    note[8].x = 'G'; note[8].sy = '#'; note[8].freq = 0;
    note[9].x = 'A'; note[9].sy = ' '; note[9].freq = 0;
    note[10].x = 'B'; note[10].sy = ' '; note[10].freq = 0;
    note[11].x = 'H'; note[11].sy = ' '; note[11].freq = 0;

    char s[100];
    scanf("%[^\n]", s);
    int n = strlen(s);

    char c[3];
    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] != ' ')
        {
           c[idx++] = s[i]; 
        }
        else{
            
            for (int j = 0; j < 12; j++)
            {
                if (note[j].x == c[0])
                {
                    if (idx == 2 && c[1] == '#') j++;
                    note[j].freq++;
                    break;
                }
            }
            idx = 0;
            c[0] = 'P';
        }
    }
    if (idx > 0)
    {
        for (int j = 0; j < 12; j++)
        {
            if (note[j].x == c[0])
            {
                if (idx == 2 && c[1] == '#') j++;
                note[j].freq++;
                break;
            }
        }
    }

    /* for (int i = 0; i < 12; i++) */
    /* { */
    /*     printf("%d ", note[i].freq); */
    /* } */
    /* printf("\n"); */

    int arr[3];
    int k = 0;
    for (int i = 0; i < 12; i++)
    {
        if (note[i].freq)
        {
            arr[k++] = i;
        }
    }

    int d1 = arr[1] - arr[0];
    int d2 = arr[2] - arr[1];
    int d3 = (arr[0] + 12) - arr[2];

    if ((d1 == 4 && d2 == 3)  ||
        (d2 == 4 && d3 == 3)  ||
        (d3 == 4 && d1 == 3)) 
    {
        printf("major\n");
    }
    else if ((d1 == 3 && d2 == 4) ||
             (d2 == 3 && d3 == 4) ||
             (d3 == 3 && d1 == 4))
    {
        printf("minor\n");
    }
    else
    {
        printf("strange\n");
    }
}

int main()
{
    solve();
    return 0;
}
