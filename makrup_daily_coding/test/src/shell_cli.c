#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
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
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Type commands to execute, or 'exit' to quit.\n");

    while (1) {
		printf("> "); 
		fflush(stdout); 
        fgets(input, BUFFER_SIZE, stdin);

        // Send input to server
        send(client_fd, input, strlen(input), 0);

        if (strcmp(input, "exit") == 0) break;

        // Receive and print the server's response
        ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) break;
        buffer[bytes_received] = '\0';
		printf("%s", buffer);
		fflush(stdout); 
    }

    // Close the connection
    close(client_fd);
    printf("Disconnected.\n");
    return 0;
}

