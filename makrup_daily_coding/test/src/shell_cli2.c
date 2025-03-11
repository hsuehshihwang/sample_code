#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // Change this to the server's IP address
#define PORT 54188
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];

    // Create a socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        close(client_fd);
        return 1;
    }

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_fd);
        return 1;
    }

    printf("Connected to server. Type commands to execute or 'exit' to quit.\n");

    // Main interaction loop
    while (1) {
        // Wait for server output
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(client_fd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        int max_fd = (client_fd > STDIN_FILENO) ? client_fd : STDIN_FILENO;

        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            perror("select failed");
            break;
        }

        // If server sends data
        if (FD_ISSET(client_fd, &read_fds)) {
            ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received <= 0) {
                printf("Server disconnected.\n");
                break;
            }
            buffer[bytes_received] = '\0';
#if 0
			printf("len(%ld) buffer[bytes_received-1]('%c') data: [", bytes_received, buffer[bytes_received-1]); 
			for(int i=0; i<bytes_received; i++) printf("%02x%s", buffer[i], i!=bytes_received-1?",":""); 
			printf("]\n"); 
#endif
			printf("%s", buffer); // Print server output to stdout
			fflush(stdout); 
        }

        // If user types input
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
                printf("Input error.\n");
                break;
            }
            if (strcmp(input, "exit\n") == 0) {
                printf("Exiting...\n");
                break;
            }
			send(client_fd, input, strlen(input), 0); // Send user input to server
        }
    }

    close(client_fd);
    return 0;
}

