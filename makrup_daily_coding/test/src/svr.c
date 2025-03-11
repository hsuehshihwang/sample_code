#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
#if 1
	int sock=socket(AF_INET, SOCK_STREAM, 0); 
	if(sock>0){
		int ret=0; 
		int opt=1; 
		ret=setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt)); 
		if(ret!=0) goto err; 
		struct sockaddr_in addr; 
		addr.sin_family=AF_INET; 
		addr.sin_port=htons(54188); 
		// addr.sin_addr.s_addr=inet_addr("0.0.0.0"); // INADDR_ANY
		addr.sin_addr.s_addr=INADDR_ANY;
		ret=bind(sock, (struct sockaddr *)&addr, sizeof(addr)); 
		if(ret!=0){
			perror("bind error"); 
			goto err; 
		} 
		ret=listen(sock, 5); 
		if(ret!=0){
			perror("listen error"); 
			goto err; 
		} 
		int cli_sock=0; 
		struct sockaddr cli_addr; 
		socklen_t cli_addr_len=sizeof(cli_addr); 
		cli_sock=accept(sock, (struct sockaddr *)&cli_addr, &cli_addr_len); 
		if(cli_sock==-1){
			perror("accept error"); 
			goto err; 
		} 
		typedef struct cmd_t {
			int magic; 
			int type; 
			int len; 
		} cmd; 
		enum cmd_type {
			CMD_MSG=1, 
			CMD_FILE_CREATE, 
			CMD_FILE_APPEND,
			CMD_FILE_REMOVE, 
			CMD_END
		}; 
		cmd cli_cmd; 
#define CMD_MAGIC 0X11223344
#define CMD_FILE_DIR "/tmp"
		while(1){
			int len=recv(cli_sock, (void *)&cli_cmd, sizeof(cli_cmd), 0); 
			if(len>0){
				cli_cmd.magic=htonl(cli_cmd.magic); 
				cli_cmd.type=htonl(cli_cmd.type); 
				cli_cmd.len=htonl(cli_cmd.len); 
				printf("%s@%d: recv(len(%d)), cli_cmd(type(%08X), len(%d))\n", __FUNCTION__, __LINE__, len, cli_cmd.type, cli_cmd.len); 
				if(cli_cmd.magic==CMD_MAGIC){
					uint8_t *data=NULL; 
					if(cli_cmd.len>0){
						data=malloc(sizeof(cli_cmd.len)); 
						if(data){
							len=recv(cli_sock, (void *)data, cli_cmd.len, 0); 
							printf("data(["); 
							for(int i=0; i<len; i++){
								printf("%02x%s", data[i], i!=len-1?",":""); 
							}
							printf("])\n"); 
						}else{
							printf("%s@%d: cli_sock(%d)) memory allocation error!!\n", __FUNCTION__, __LINE__, cli_sock); 
							close(cli_sock); 
							break; 
						}
					}else{
						printf("%s@%d: cli_sock(%d)) cmd len zero!!\n", __FUNCTION__, __LINE__, cli_sock); 
					}
					switch(cli_cmd.type){
						case CMD_MSG: 
							{
								if(data){
									char *msg=strndup((const char *)data, cli_cmd.len+1); 
									msg[cli_cmd.len]='\0'; 
									printf("CMD_MSG(\"%s\")\n", msg); 
								}
							}
							break; 
						case CMD_FILE_CREATE: 
							{
								if(data){
									char *filename=strndup((const char *)data, cli_cmd.len); 
									if(filename){
										filename[cli_cmd.len]='\0'; 
										printf("CMD_FILE_CREATE(\"%s\")\n", filename); 
										char *filepath=malloc(cli_cmd.len+strlen(CMD_FILE_DIR)+1); 
										if(filepath){
											sprintf(filepath, "%s/%s", CMD_FILE_DIR, filename); 
											printf("filepath(%s)\n", filepath); 
											if(!access(filepath, F_OK)){
												printf("remove(%s)\n", filepath); 
												remove(filepath); 
											}
											// int fd=open(filepath, O_CREAT, S_IRWXU|S_IRUSR|S_IWUSR); 
											int fd=open(filepath, O_CREAT, 0666); 
											if(fd>0){
												close(fd); 
											}
											free(filepath); 
										}
										free(filename);
									}
								}
							}
							break; 
						case CMD_FILE_REMOVE: 
							{
								if(data){
									char *filename=strndup((const char *)data, cli_cmd.len); 
									if(filename){
										filename[cli_cmd.len]='\0'; 
										printf("CMD_FILE_REMOVE(\"%s\")\n", filename); 
										char *filepath=malloc(cli_cmd.len+strlen(CMD_FILE_DIR)+1); 
										if(filepath){
											sprintf(filepath, "%s/%s", CMD_FILE_DIR, filename); 
											printf("filepath(%s)\n", filepath); 
											if(!access(filepath, F_OK)){
												printf("remove(%s)\n", filepath); 
												remove(filepath); 
											}
											free(filepath); 
										}
										free(filename);
									}
								}
							}
							break; 
						case CMD_FILE_APPEND: 
							{
								if(data){
									char *filename=strndup((const char *)data, cli_cmd.len); 
									if(filename){
										printf("CMD_FILE_APPEND(\"%s\")\n", filename); 
										if(strlen(filename)+1<cli_cmd.len){
											char *filepath=malloc(strlen(filename)+strlen(CMD_FILE_DIR)+1); 
											if(filepath){
												if(!access(filepath, F_OK)){
													printf("F_OK(%s)\n", filepath); 
												}
												sprintf(filepath, "%s/%s", CMD_FILE_DIR, filename); 
												printf("filepath(%s)\n", filepath); 
												int fd=open(filepath, O_WRONLY|O_APPEND|O_CREAT, 0666);
												if(fd>0){
													do{
														if(flock(fd, LOCK_EX)<0){
															close(fd);
															break; 
														}
														// Write data to the file
														if(write(fd, data+strlen(filename)+1, cli_cmd.len-strlen(filename)-1)<0){
															flock(fd, LOCK_UN); // Unlock the file before exiting
															close(fd);
															break; 
														}
														if(flock(fd, LOCK_UN)<0){
															close(fd);
															break; 
														}
													}while(0); 
												}
												free(filepath); 
											}
										}
										free(filename);
									}
								}
							}
							break; 
						default: 
							{
							}
							break; 
					}
					if(data) free(data); 
				}else{
					printf("%s@%d: cli_sock(%d)) magic error!!\n", __FUNCTION__, __LINE__, cli_sock); 
					close(cli_sock); 
					break; 
				}
			}else if(len==0){
				printf("%s@%d: cli_sock(%d)) leave!!\n", __FUNCTION__, __LINE__, cli_sock); 
				close(cli_sock); 
				break; 
			}else{
				close(cli_sock); 
				goto err; 
			}
			usleep(10); 
		}
	}else goto err; 
	printf("%s@%d: close(sock(%d))\n", __FUNCTION__, __LINE__, sock); 
	if(sock>0) close(sock); 
	return 0; 
err: 
	printf("%s@%d: err!!\n", __FUNCTION__, __LINE__); 
	if(sock>0) close(sock); 
#endif
	return 0; 
}
