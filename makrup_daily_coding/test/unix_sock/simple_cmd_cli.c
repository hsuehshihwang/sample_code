#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/un.h>
#include "cmd.h"
void handle_cmd_test(int sock){
	cmd client_cmd; 
	client_cmd.magic=htonl(CMD_MAGIC); 
	client_cmd.type=htonl(CMD_TEST); 
	client_cmd.length=0; 
	send(sock, &client_cmd, sizeof(cmd), 0); 
}
void handle_cmd_shell(int sock){
	cmd client_cmd; 
	client_cmd.magic=htonl(CMD_MAGIC); 
	client_cmd.type=htonl(CMD_SHELL); 
	client_cmd.length=0; 
	send(sock, &client_cmd, sizeof(cmd), 0); 
	printf("Sleep 1 sec...\n"); 
	sleep(1); 
#define BUFFER_SIZE 1024
    // char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];
	char peek; 
    printf("Connected to server. Type commands to execute, or 'exit' to quit.\n");
    while (1) {
		printf("> "); 
		fflush(stdout); 
        fgets(input, BUFFER_SIZE, stdin);

        // Send input to server
        send(sock, input, strlen(input), 0);

        if (strcmp(input, "exit") == 0) break;

		ssize_t bytes_received; 
		// printf("before peek...\n"); 
        bytes_received=recv(sock, &peek, 1, MSG_PEEK);
		if(bytes_received<=0) break; 
		int bytes_available; 
		ioctl(sock, FIONREAD, &bytes_available); 
		uint8_t *data=malloc(bytes_available+1); 
		if(data){
			bytes_received=recv(sock, data, bytes_available, 0);
			if (bytes_received<=0) break;
			data[bytes_received] = '\0';
			printf("%s", data);
			fflush(stdout); 
			free(data); 
		}else{
			break; 
		}
#if 0
        // Receive and print the server's response
        ssize_t bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) break;
        buffer[bytes_received] = '\0';
		printf("%s", buffer);
		fflush(stdout); 
#endif
    }
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	int sock=socket(AF_UNIX, SOCK_STREAM, 0); 
	int opt=1; 
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	struct sockaddr_un addr; 
	addr.sun_family=AF_UNIX; 
	strncpy(addr.sun_path, "/tmp/socket_un_test", sizeof(addr.sun_path)); 
	connect(sock, (struct sockaddr *)&addr, sizeof(addr)); 
	if(argc>1&&!strcmp(argv[1], "shell")){
		handle_cmd_shell(sock); 
	}else if(argc>1&&!strcmp(argv[1], "test")){
		handle_cmd_test(sock); 
	}else{
		handle_cmd_shell(sock); 
	}
	close(sock); 
	return 0; 
}
