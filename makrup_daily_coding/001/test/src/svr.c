#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
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
		cmd cli_cmd; 
#define CMD_MAGIC 0X11223344
		while(1){
			int len=recv(cli_sock, (void *)&cli_cmd, sizeof(cli_cmd), 0); 
			if(len>0){
#if 1
				cli_cmd.magic=htonl(cli_cmd.magic); 
				cli_cmd.type=htonl(cli_cmd.type); 
				cli_cmd.len=htonl(cli_cmd.len); 
				printf("%s@%d: recv(len(%d)), cli_cmd(type(%08X), len(%d))\n", __FUNCTION__, __LINE__, len, cli_cmd.type, cli_cmd.len); 
				if(cli_cmd.magic==CMD_MAGIC){
					if(cli_cmd.len>0){
						uint8_t *data=malloc(sizeof(cli_cmd.len)); 
						if(data){
							len=recv(cli_sock, (void *)data, cli_cmd.len, 0); 
							printf("data(["); 
							for(int i=0; i<len; i++){
								printf("%02x%s", data[i], i!=len-1?",":""); 
							}
							printf("])\n"); 
							free(data); 
						}else{
							printf("%s@%d: cli_sock(%d)) memory allocation error!!\n", __FUNCTION__, __LINE__, cli_sock); 
							close(cli_sock); 
							break; 
						}
					}else{
						printf("%s@%d: cli_sock(%d)) cmd len zero!!\n", __FUNCTION__, __LINE__, cli_sock); 
					}
				}else{
					printf("%s@%d: cli_sock(%d)) magic error!!\n", __FUNCTION__, __LINE__, cli_sock); 
					close(cli_sock); 
					break; 
				}
#else
				printf("%s@%d: recv(len(%d)), cli_cmd(type(%08X), len(%d))\n", __FUNCTION__, __LINE__, len, htonl(cli_cmd.type), htonl(cli_cmd.len)); 
				cli_cmd.magic=htonl(cli_cmd.magic); 
				if(cli_cmd.magic==CMD_MAGIC){
					cli_cmd.type=htonl(cli_cmd.type); 
					cli_cmd.len=htonl(cli_cmd.len); 
					if(cli_cmd.len>0){
						// uint8_t data[256]={0}; 
						uint8_t *data=malloc(256); 
						len=recv(cli_sock, (void *)data, cli_cmd.len, 0); 
						printf("%s@%d: data coming!!\n", __FUNCTION__, __LINE__); 
						printf("data(["); 
						for(int i=0; i<len; i++){
							printf("%02x%s", data[i], i!=len-1?",":""); 
						}
						printf("])\n"); 
						free(data); 
					}
				}
#endif
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
