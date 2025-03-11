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
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	int sock=socket(AF_UNIX, SOCK_STREAM, 0); 
	int opt=1; 
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	unlink("/tmp/socket_un_test"); 
	struct sockaddr_un addr; 
	addr.sun_family=AF_UNIX; 
	strncpy(addr.sun_path, "/tmp/socket_un_test", sizeof(addr.sun_path)); 
	bind(sock, (struct sockaddr *)&addr, sizeof(addr)); 
	listen(sock, 5); 
	int client_sock=0; 
	while(1){
		fd_set rfds; 
		FD_ZERO(&rfds); 
		FD_SET(sock, &rfds); 
		struct timeval tv, tv_bkp; 
		tv.tv_sec=5; 
		tv.tv_usec=0; 
		tv_bkp=tv; 
		int max_sock=sock; 
		if(client_sock>0){
			FD_SET(client_sock, &rfds); 
			if(client_sock>max_sock) max_sock=client_sock; 
		}
		int ret=select(max_sock+1, &rfds, NULL, NULL, 0); 
		if(ret<0){
			perror("select error!!"); 
		}else if(ret==0){
			printf("timeout(%ld)\n", tv_bkp.tv_sec); 
		}else{
			if(FD_ISSET(sock, &rfds)){
				struct sockaddr_un client_addr; 
				socklen_t client_addrlen=sizeof(client_addr); 
				client_sock=accept(sock, (struct sockaddr *)&client_addr, &client_addrlen); 
				printf("client_sock(%d)\n", client_sock); 
			}
			if(FD_ISSET(client_sock, &rfds)){
				int bytes_available; 
				ioctl(client_sock, FIONREAD, &bytes_available); 
				printf("bytes_available(%d)\n", bytes_available); 
				if(bytes_available<=0){
					printf("Client disconnected!!\n"); 
					break; 
				}
				uint8_t *data=malloc(bytes_available+1); 
				ssize_t bytes_received=recv(client_sock, data, bytes_available, 0); 
				data[bytes_received]='\0'; 
				printf("data received: ["); 
				for(int i=0; i<bytes_received; i++){
					printf("0x%02x%s", data[i], i!=bytes_received-1?" ":""); 
				}
				printf("]: %s\n", data); 
			}
		}
	}
	close(sock); 
	return 0; 
}
