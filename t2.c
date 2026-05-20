#include <stdio.h>
#include <unistd.h> // For usleep

int main() {
    // 1. Clear the screen once at the start
    printf("\033[2J"); 

    float cpu_usage = 0.0;
    int ram_usage = 2048;

    for (int i = 0; i < 50; i++) {
        // 2. Move cursor to top-left (1,1) to rewrite
        printf("\033[H"); 

        printf("\033[1;36mSYSTEM MONITOR (Updating...)\033[0m\n");
        printf("------------------------------------\n");
        
        // Using Width Padding and Precision
        // %-10s -> Left align string in 10 spaces
        // %6.2f -> 6 total width, 2 decimal places
        // %+d    -> Force the + sign to show (for "change")
        printf("%-10s : %6.2f%%\n", "CPU", cpu_usage);
        printf("%-10s : %6d MB (%+d)\n", "RAM", ram_usage, (i % 2 == 0 ? 5 : -3));
        
        printf("------------------------------------\n");

        // Simulate data changing
        cpu_usage += 1.5;
        ram_usage += (i % 2 == 0 ? 5 : -3);

        fflush(stdout); 
        usleep(200000); // Update every 0.2 seconds
    }

    printf("\nMonitoring Complete.\n");
    return 0;
}
