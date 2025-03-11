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
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	int sock=socket(AF_INET, SOCK_STREAM, 0); 
	int opt=1; 
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	struct sockaddr_in addr; 
	addr.sin_family=AF_INET; 
	addr.sin_port=htons(54188); 
	addr.sin_addr.s_addr=inet_addr("0.0.0.0"); // INADDR_ANY
	bind(sock, (struct sockaddr *)&addr, sizeof(addr)); 
	listen(sock, 5); 
	struct sockaddr_in client_addr; 
	socklen_t client_addrlen=sizeof(client_addr); 
	int client_sock=accept(sock, (struct sockaddr *)&client_addr, &client_addrlen); 
	while(1){
		char c; 
		ssize_t bytes_peeked=recv(client_sock, &c, 1, MSG_PEEK); 
		if(bytes_peeked<=0) break; 
		int bytes_available; 
		ioctl(client_sock, FIONREAD, &bytes_available); 
		printf("bytes_available(%d)\n", bytes_available); 
		uint8_t *data=malloc(bytes_available+1); 
		ssize_t bytes_received=recv(client_sock, data, bytes_available, 0); 
		data[bytes_received]='\0'; 
		printf("data received: ["); 
		for(int i=0; i<bytes_received; i++){
			printf("0x%02x%s", data[i], i!=bytes_received-1?" ":""); 
		}
		printf("]: %s\n", data); 
	}
	close(client_sock); 
	close(sock); 
	return 0; 
}
