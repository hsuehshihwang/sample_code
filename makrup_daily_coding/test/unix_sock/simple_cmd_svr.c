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
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "cmd.h"
int handle_cmd_shell(int sock, int client_sock){
	do{
		printf("CMD_SHELL()\n"); 
		pid_t pid=fork();
		if(pid<0){
			perror("Fork failed");
			close(client_sock);
			return -1; 
		}
		if(pid==0){ // Child process
			dup2(client_sock, STDIN_FILENO);
			dup2(client_sock, STDOUT_FILENO);
			dup2(client_sock, STDERR_FILENO);
			close(client_sock);
			close(sock);
			execl("/bin/sh", "sh", NULL);
			perror("execl failed");
			exit(EXIT_FAILURE); 
		}else{
			waitpid(pid, NULL, 0);
			printf("Shell session ended.\n");
			close(client_sock); 
		}
	}while(0); 
	return 0; 
}
int handle_cmd_shell2(int sock, int client_sock){
	do{
		printf("CMD_SHELL()\n"); 
		int pipe_fd[2]; 
		if(pipe(pipe_fd)==-1){
			perror("pipe failed");
			close(client_sock);
			return -1; 
		}
		pid_t pid=fork();
		if(pid<0){
			perror("Fork failed");
			close(client_sock);
			return -1; 
		}
		if(pid==0){ // Child process
			pid_t child_pid; 
			child_pid=fork(); 
			if(child_pid==-1){
			}
			if(child_pid==0){
				dup2(pipe_fd[1], STDOUT_FILENO);
				dup2(pipe_fd[1], STDERR_FILENO); 
				close(pipe_fd[0]); 
				close(pipe_fd[1]); 
				close(client_sock);
				close(sock);
				waitpid(pid, NULL, 0);
				exit(0); 
			}else{
				dup2(client_sock, STDIN_FILENO);
				dup2(client_sock, STDOUT_FILENO);
				dup2(client_sock, STDERR_FILENO);
				close(pipe_fd[0]); 
				close(pipe_fd[1]); 
				close(client_sock);
				close(sock);
				execl("/bin/sh", "sh", NULL);
				perror("execl failed");
				exit(EXIT_FAILURE); 
			}
		}else{
			close(pipe_fd[1]); 
			int flags=fcntl(pipe_fd[0], F_GETFL, 0);
			fcntl(pipe_fd[0], F_SETFL, flags|O_NONBLOCK);
			int status; 
			while(1){
				printf("before using waitpid...\n"); 
				sleep(1); 
				pid_t result=waitpid(pid, &status, WNOHANG); 
				if(result==-1){
					perror("waitpid failed");
					break;
				}else if(result>0){
					if(WIFEXITED(status)){
						printf("Child exited with status %d\n", WEXITSTATUS(status));
					}else if(WIFSIGNALED(status)){
						printf("Child terminated by signal %d\n", WTERMSIG(status));
					}
					break; 
				}
				int bytes_available; 
				ioctl(pipe_fd[0], FIONREAD, &bytes_available); 
				if(bytes_available>0) printf("bytes_available(%d)\n", bytes_available); 
				if(bytes_available<0) break; 
				if(bytes_available==0) continue; 
				uint8_t *data=malloc(bytes_available+1); 
				if(data){
					ssize_t bytes_read=read(pipe_fd[0], data, bytes_available);
					if (bytes_read>0) {
						data[bytes_read] = '\0';
						printf("%s", data); 
						fflush(stdout); 
					}else if(bytes_read==-1&&errno!=EAGAIN) {
						perror("read failed");
						break;
					}
				}else{
					break; 
				}
				usleep(100000); 
			}
			printf("Shell session ended.\n");
			close(pipe_fd[0]); 
			close(client_sock); 
		}
	}while(0); 
	return 0; 
}
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
	struct sockaddr_un client_addr; 
	socklen_t client_addrlen=sizeof(client_addr); 
	int client_sock=0; 
	while(1){
		if(client_sock>0){
			do{
				cmd client_cmd; 
				ssize_t bytes_received=recv(client_sock, &client_cmd, sizeof(cmd), 0); 
				printf("bytes_received(%ld)\n", bytes_received); 
				if(bytes_received!=sizeof(cmd)){
					printf("client disconnected!!\n"); 
					close(client_sock); 
					client_sock=0; 
					break; 
				} 
				client_cmd.magic=ntohl(client_cmd.magic); 
				client_cmd.type=ntohl(client_cmd.type); 
				client_cmd.length=ntohl(client_cmd.length); 
				printf("cmd(magic(%08X),type(%08X)(%s),length(%d))\n", client_cmd.magic, client_cmd.type, get_cmd_type_desc(client_cmd.type), client_cmd.length); 
				if(client_cmd.magic!=CMD_MAGIC){
					printf("magic error!!\n"); 
					close(client_sock); 
					client_sock=0; 
					break; 
				}
				if(client_cmd.length>0){
					uint8_t *data=malloc(client_cmd.length+1); 
					if(data){
						bytes_received=recv(client_sock, data, client_cmd.length, 0); 
						data[bytes_received]='\0'; 
						printf("data received: ["); 
						for(int i=0; i<bytes_received; i++){
							printf("0x%02x%s", data[i], i!=bytes_received-1?" ":""); 
						}
						printf("]: %s\n", data); 
						switch (client_cmd.type){
							case CMD_MSG: 
								{
									printf("CMD_MSG(%s)\n", data); 
								}
								break; 
							default: 
								{
									printf("command not supported with data len(%d)!!\n", client_cmd.length); 
									close(client_sock); 
									client_sock=0; 
								}
								break; 
						}
					}else{
						printf("mem alloc error!!\n"); 
						close(client_sock); 
						client_sock=0; 
						break; 
					}
				}else{
					switch (client_cmd.type){
						case CMD_TEST: 
							{
								printf("CMD_TEST()\n"); 
							}
							break; 
						case CMD_SHELL: 
							{
								handle_cmd_shell2(sock, client_sock); 
							}
							break; 
						default: 
							{
								printf("command not supported with data len 0!!\n"); 
								close(client_sock); 
								client_sock=0; 
							}
							break; 
					}
				}
			}while(0); 
		}else{
			client_sock=accept(sock, (struct sockaddr *)&client_addr, &client_addrlen); 
			printf("new client connected!!\n"); 
		}
	}
	close(client_sock); 
	close(sock); 
	return 0; 
}
