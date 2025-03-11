#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <sys/time.h>

#define dbg(fmt,...) printf("%s@%d: "fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

int main(int argc, char *argv[]){
	int svr_fd=socket(SOCK_STREAM, AF_INET, 0); 
	if(svr_fd>0){
		int optval=1; 
		setsockopt(svr_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); 
		struct sockaddr_in svr_addr; 
		svr_addr.sin_family=AF_INET; 
		svr_addr.sin_port=htons(54188); 
		svr_addr.sin_addr.s_addr=inet_addr("0.0.0.0"); 
		bind(svr_fd, (struct sockaddr *)&svr_addr, sizeof(svr_addr)); 
		listen(svr_fd, 5); 
		int max_cli=5; 
		int cli_fds[max_cli];
		for(int i=0; i<max_cli; i++) cli_fds[i]=0; 
		while(1){
			fd_set rfds; 
			FD_ZERO(&rfds); 
			FD_SET(svr_fd, &rfds); 
			int max_fd=svr_fd; 
			for(int i=0; i<max_cli; i++){
				if(cli_fds[i]!=0){
					FD_SET(cli_fds[i], &rfds);
					if(cli_fds[i]>max_fd) max_fd=cli_fds[i]; 
				}
			}
			struct timeval tv; 
			tv.tv_sec=5; 
			tv.tv_usec=0; 
			int ret=select(max_fd+1, &rfds, NULL, NULL, &tv); 
			if(ret<0){
				perror("select error"); 
			}else if(ret>0){
				if(FD_ISSET(svr_fd, &rfds)){
					struct sockaddr_in cli_addr; 
					socklen_t cli_addr_len=sizeof(cli_addr); 
					int cli_fd=	accept(svr_fd, (struct sockaddr *)&cli_addr, &cli_addr_len); 
					dbg("client(%s:%d) connected!!", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port)); 
					for(int i=0; i<max_cli; i++){
						if(cli_fds[i]==0){
							cli_fds[i]=cli_fd; 
							break; 
						}
					}
				}
				for(int i=0; i<max_cli; i++){
					if(FD_ISSET(cli_fds[i], &rfds)){
						dbg("client(%d) has data!!", cli_fds[i]); 
					}
				}
			}else{
				dbg("5 sec timeout"); 
				// you can check all clients
			}
		}
		close(svr_fd); 
	}
	return 0; 
}
