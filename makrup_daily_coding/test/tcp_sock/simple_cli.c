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
	addr.sin_addr.s_addr=inet_addr("127.0.0.1"); 
	connect(sock, (struct sockaddr *)&addr, sizeof(addr)); 
	char data[]="Hello! I'm Ralph!!"; 
	send(sock, data, strlen(data), 0); 
	printf("Sleep 5 sec...\n"); 
	sleep(5); 
	close(sock); 
	return 0; 
}
