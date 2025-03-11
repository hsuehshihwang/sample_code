#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>
int main(void){
	int fd=socket(AF_UNIX, SOCK_STREAM, 0); 
	if(fd<0){
		perror("socket error!!"); 
		goto err; 
	}
	unlink("/tmp/socket_un_test"); 
	struct sockaddr_un addr; 
	addr.sun_family=AF_UNIX; 
	strncpy(addr.sun_path, "/tmp/socket_un_test", sizeof(addr.sun_path)); 
	socklen_t addrlen=sizeof(addr); 
	int ret=bind(fd, (struct sockaddr *)&addr, addrlen); 
	if(ret==-1){
		perror("bind error!!"); 
		goto err; 
	}
	ret=listen(fd, 5); 
	if(ret==-1){
		perror("listen error!!"); 
	}
	int max_fd=fd; 
	int client_fds[5]={0}; 
	fd_set rfds; 
	while(1){
		struct timeval timeout, timeout_bkp; 
		FD_ZERO(&rfds); 
		FD_SET(fd, &rfds); 
		max_fd=fd; 
		for(int i=0; i<5; i++){
			if(client_fds[i]>0){
				FD_SET(client_fds[i], &rfds); 
				if(client_fds[i]>max_fd) max_fd=client_fds[i]; 
			}
		}
		timeout.tv_sec=5; 
		timeout.tv_usec=0; 
		timeout_bkp=timeout; 
		ret=select(max_fd+1, &rfds, NULL, NULL, &timeout); 
		printf("ret(%d)\n", ret); 
		if(ret==0){
			printf("timeout(%ld sec, %ld usec)\n", timeout_bkp.tv_sec, timeout_bkp.tv_usec); 
		}else if(ret>0){
			if(FD_ISSET(fd, &rfds)){
				struct sockaddr_un client_addr; 
				socklen_t client_addrlen; 
				int new_client_fd=accept(fd, (struct sockaddr *)&client_addr, &client_addrlen); 
				if(new_client_fd>0){
					printf("new_client_fd(%d)\n", new_client_fd); 
					for(int i=0; i<5; i++){
						if(client_fds[i]==0){
							client_fds[i]=new_client_fd; 
							break; 
						}
					}
				}else{
					perror("accept error!!"); 
					continue; 
				}
			}
			for(int i=0; i<5; i++){
				if(FD_ISSET(client_fds[i], &rfds)){
					int flags = fcntl(fd, F_GETFL, 0);
					printf("Blocking state: %s\n", (flags & O_NONBLOCK) ? "Non-blocking" : "Blocking");
					int bytes_available; 
					ret=ioctl(client_fds[i], FIONREAD, &bytes_available); 
					if(ret<0){
						perror("ioctl error!!"); 
						break; 
					}
					printf("bytes_available(%d)\n", bytes_available); 
					if(bytes_available==0){
						close(client_fds[i]); 
						client_fds[i]=0; 
					}else if(bytes_available>0){
						ssize_t bytes_received; 
						uint8_t *data=malloc(bytes_available+1); 
						if(data){
							do{
								bytes_received=recv(client_fds[i], data, bytes_available, 0); 
								if(bytes_received<=0) break; 
								data[bytes_received]='\0'; 
								printf("bytes_received(%ld)\n", bytes_received); 
								printf("data received: ["); 
								for(int j=0; j<bytes_received; j++){
									printf("%02x%s", data[j], j!=bytes_received-1?" ":""); 
								}
								printf("]\n"); 
							}while(0); 
							free(data); 
						}
					}else{
					}
				}
			}
			sleep(1); 
			// data
		}else{
			perror("select error!!"); 
		}
		usleep(10); 
	}
err: 
	if(fd>0) close(fd); 
	return 0; 
}
