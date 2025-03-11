#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <stdint.h>
#include "debug.h"

#define WIDTH 10
#define HEIGHT 20

void drawBoard() {
    system("clear"); // Clear screen (use "cls" on Windows)
    
    // Draw top border
    printf("+");
    for (int i = 0; i < WIDTH; i++) {
        printf("O");
    }
    printf("+\n");

    // Draw board with side borders
    for (int row = 0; row < HEIGHT; row++) {
        printf("O");  // Left border
        for (int col = 0; col < WIDTH; col++) {
            printf(" "); // Empty space for the game area
        }
        printf("O");  // Right border
        printf("\n");
    }

    // Draw bottom border
    printf("+");
    for (int i = 0; i < WIDTH; i++) {
        printf("O");
    }
    printf("+\n");
}

int main() {
    while (1) { // Continuous loop to refresh board
        drawBoard();
        usleep(500000); // Pause for 0.5 seconds
    }
    return 0;
}

