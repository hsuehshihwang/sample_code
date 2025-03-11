#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdint.h>

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 

#define REPEAT_5(C) C C C C C
#define REPEAT_10(C) REPEAT_5(C) REPEAT_5(C)
#define REPEAT_20(C) REPEAT_10(C) REPEAT_10(C)
#define REPEAT_40(C) REPEAT_20(C) REPEAT_20(C)
#define REPEAT_80(C) REPEAT_40(C) REPEAT_40(C)

#define REPEAT(C,n) REPEAT_##n(C)

#define FUNC_BAR REPEAT("=",20)

#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
		fflush(stdout); \
    } while(0); 


typedef struct cliInfo {
	int sock; 
	struct timeval tv; 
} cliInfo; 

int main(int argc, char *argv[]){
	dbge(); 
	int svr_sock=socket(AF_INET, SOCK_STREAM, 0); 
	if(svr_sock>0){
		int optval=1; 
		setsockopt(svr_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); 
		struct sockaddr_in svr_addr; 
		svr_addr.sin_family=AF_INET; 
		svr_addr.sin_port=htons(54188); 
		svr_addr.sin_addr.s_addr=inet_addr("0.0.0.0");  // INADDR_ANY
		bind(svr_sock, (const struct sockaddr *)&svr_addr, sizeof(svr_addr)); 
		listen(svr_sock, 5); 
		int max_fd=svr_sock; 
		fd_set rfds, wfds;
		struct timeval tv;
		int retval;
#define MAX_CLIENTS 10
		int cli_socks[MAX_CLIENTS]; 
		for(int i=0; i<MAX_CLIENTS; i++){
			cli_socks[i]=0; 
		}
		while(1){
			FD_ZERO(&rfds);
			FD_ZERO(&wfds);
			max_fd=svr_sock; 
			FD_SET(svr_sock, &rfds); 
			tv.tv_sec = 10;
			tv.tv_usec = 0;
			for(int i=0; i<MAX_CLIENTS; i++){
				if(cli_socks[i]>0){
					dbge("cli_socks[%i]: %d", i, cli_socks[i]); 
					FD_SET(cli_socks[i], &rfds); 
					// FD_SET(cli_socks[i], &wfds); 
					if(cli_socks[i]>max_fd) max_fd=cli_socks[i]; 
				}
			}
			dbge("before select, max_fd(%d)...", max_fd); 
			// retval = select(max_fd+1, &rfds, &wfds, NULL, &tv);
			retval = select(max_fd+1, &rfds, NULL, NULL, &tv);
			if(retval==-1){
				dbge("select error!!"); 
			}else if(retval){
				if(FD_ISSET(svr_sock, &rfds)){
					dbge("before accept..."); 
					struct sockaddr_in cli_addr; 
					socklen_t cli_socklen=0; 
					int cli_sock=accept(svr_sock, (struct sockaddr *)&cli_addr, &cli_socklen); 
					if(cli_sock<0){
						dbge("accept error..."); 
						continue; 
					}
					dbge("New connection from %s:%d",
							inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
					if(cli_sock>0){
						for(int i=0; i<MAX_CLIENTS; i++){
							if(cli_socks[i]==0){
								cli_socks[i]=cli_sock; 
								break; 
							}
						}
					}
				}
				for(int i=0; i<MAX_CLIENTS; i++){
					if(FD_ISSET(cli_socks[i], &rfds)){
						int bytes_available;

						// Query the size of incoming data
						if (ioctl(cli_socks[i], FIONREAD, &bytes_available) < 0) {
							dbge("ioctl(FIONREAD) failed");
							close(cli_socks[i]);
							continue;
						}
						dbge("data coming: len(%d)", bytes_available); 
						if(bytes_available==0){
							close(cli_socks[i]); 
							cli_socks[i]=0;
						}else if(bytes_available>0){
							char buf[128]={0}; 
							// dbge("cli(%d) send data", i); 
							recv(cli_socks[i], buf, sizeof(buf)-1, 0); 
							buf[sizeof(buf)-1]='\0'; 
							dbge("cli[%d]: recv(\"%s\")", cli_socks[i], buf); 
							FD_SET(cli_socks[i], &wfds); 
						}
					}
					if(FD_ISSET(cli_socks[i], &wfds)){
						send(cli_socks[i], "ACK", 3, 0); 
					}
				}
			}else{
				dbge("select() 10 sec timeout..."); 
			}
		}
		close(svr_sock); 
	}
	exit(EXIT_SUCCESS);
}

