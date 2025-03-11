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
#include <fcntl.h>
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
    // Set stdin to non-blocking mode
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    char buffer[1024];
    ssize_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        printf("Data on stdin: %s\n", buffer);
    } else if (bytesRead == 0) {
        printf("No data on stdin (EOF reached).\n");
    } else {
        perror("read");
    }

    // Restore blocking mode (optional)
    fcntl(STDIN_FILENO, F_SETFL, flags);
	return 0; 
}
