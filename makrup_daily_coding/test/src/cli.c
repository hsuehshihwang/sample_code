#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
		addr.sin_addr.s_addr=inet_addr("127.0.0.1");
		ret=connect(sock, (struct sockaddr *)&addr, sizeof(addr)); 
		if(ret!=0){
			perror("connect error"); 
			goto err; 
		} 
		typedef struct cmd_t {
			int magic; 
			int type; 
			int len; 
		} cmd; 
		cmd cli_cmd; 
		enum cmd_type {
			CMD_MSG=1, 
			CMD_FILE_CREATE, 
			CMD_FILE_APPEND,
			CMD_FILE_REMOVE,
			CMD_END
		}; 
#define CMD_MAGIC 0X11223344
		uint8_t *data=NULL; 
		int data_len=0; 
		data=(uint8_t *)strdup("hello world!!"); 
		if(data){
			cli_cmd.magic=htonl(CMD_MAGIC); 
			cli_cmd.type=htonl(CMD_MSG); 
			data_len=strlen((const char *)data); 
			cli_cmd.len=htonl(data_len); 
			send(sock, (const void *)&cli_cmd, sizeof(cli_cmd), 0); 
			send(sock, (const void *)data, data_len, 0); 
			free(data); 
			data=NULL; 
			data_len=0; 
		}
		data=(uint8_t *)strdup("cmd_new_file"); 
		if(data){
			cli_cmd.magic=htonl(CMD_MAGIC); 
			cli_cmd.type=htonl(CMD_FILE_CREATE); 
			data_len=strlen((const char *)data); 
			cli_cmd.len=htonl(data_len); 
			send(sock, (const void *)&cli_cmd, sizeof(cli_cmd), 0); 
			send(sock, (const void *)data, data_len, 0); 
			free(data); 
			data=NULL; 
			data_len=0; 
		}
		data=(uint8_t *)strdup("cmd_new_file"); 
		if(data){
			cli_cmd.magic=htonl(CMD_MAGIC); 
			cli_cmd.type=htonl(CMD_FILE_APPEND); 
			data_len=strlen((const char *)data); 
			data=realloc(data, data_len+strlen("Ralph: hello world!!")+1); 
			if(data){
				data[data_len]='\0'; 
				strcpy((char *)data+data_len+1, "Ralph: hello world!!"); 
				data_len=data_len+1+strlen("Ralph: hello world!!"); 
				cli_cmd.len=htonl(data_len); 
				send(sock, (const void *)&cli_cmd, sizeof(cli_cmd), 0); 
				send(sock, (const void *)data, data_len, 0); 
				free(data); 
				data=NULL; 
				data_len=0; 
			}
		}
		data=(uint8_t *)strdup("cmd_append_file"); 
		if(data){
			cli_cmd.magic=htonl(CMD_MAGIC); 
			cli_cmd.type=htonl(CMD_FILE_APPEND); 
			data_len=strlen((const char *)data); 
			data=realloc(data, data_len+strlen("Ralph: hello world!!")+1); 
			if(data){
				data[data_len]='\0'; 
				strcpy((char *)data+data_len+1, "Ralph: hello world!!"); 
				data_len=data_len+1+strlen("Ralph: hello world!!"); 
				cli_cmd.len=htonl(data_len); 
				send(sock, (const void *)&cli_cmd, sizeof(cli_cmd), 0); 
				send(sock, (const void *)data, data_len, 0); 
				free(data); 
				data=NULL; 
				data_len=0; 
			}
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
