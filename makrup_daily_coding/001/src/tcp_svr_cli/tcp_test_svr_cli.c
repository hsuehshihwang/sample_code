#include "tcp_svr_cli.h"
void tcp_test_svr(void){
	enter_n_exit(); 
#if 0
	int svr_sock=socket(AF_INET, SOCK_STREAM, 0); 
	if(svr_sock>0){
		int ret=0; 
		struct sockaddr_in svr_addr; 
		int optval=1; 
		ret=setsockopt(svr_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); 
		dbge("setsocketopt(ret(%d), optval(%d))", ret, optval); 
		optval=1; 
		ret=setsockopt(svr_sock, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)); 
		dbge("setsocketopt(ret(%d), optval(%d))", ret, optval); 
		svr_addr.sin_family=AF_INET; 
		svr_addr.sin_port=htons(54188); 
		svr_addr.sin_addr.s_addr=inet_addr("0.0.0.0"); // INADDR_ANY 
		ret=bind(svr_sock, (const struct sockaddr *)&svr_addr, sizeof(svr_addr));
		if(ret!=0){
			perror("bind error"); 
			goto err; 
		}
		ret=listen(svr_sock, 5); 
		if(ret!=0){
			perror("listen error"); 
			goto err; 
		}
		struct sockaddr_in cli_addr; 
		socklen_t cli_addrlen; 
		int cli_sock=accept(svr_sock, (struct sockaddr *)&cli_addr, &cli_addrlen); 
		dbge("cli_sock(%d), addr(%s)", cli_sock, inet_ntoa(cli_addr.sin_addr)); 
		typedef struct cmd_t {
			uint32_t magic; 
			uint32_t type; 
			uint32_t len; 
		} cmd; 
		enum {
			CMD_NONE=0, 
			CMD_FILENAME, 
			CMD_FILEAPPEND, 
			CMD_END=255
		}; 
		if(cli_sock>0){
			int bytes_available=0; 
			if(ioctl(cli_sock, FIONREAD, &bytes_available)<0){
				perror("ioctl(FIONREAD) error"); 
				close(cli_sock); 
				goto err; 
			}
			cmd c;
			if(bytes_available==0){
				close(cli_sock); 
				goto err; 
			}else if(bytes_available>0){
				recv(cli_sock, (void *)&c, sizeof(c), 0); 
				if(ntohl(c.magic)!=0x11223344){
					dbge("clinet magic error(%08X)", ntohl(c.magic)); 
					close(cli_sock); 
					goto err; 
				}
				switch(ntohl(c.type)){
					case CMD_FILENAME: 
						{
							char name[c.len+1]; 
							int len=recv(cli_sock, (void *)name, sizeof(name), 0); 
							if(len!=c.len){
								close(cli_sock); 
								goto err; 
							}
							name[len]='\0'; 
							dbge("file name: %s", name); 
						}
						break; 
				}
			}else{
				close(cli_sock); 
				goto err; 
			}
			close(cli_sock); 
		}else goto err; 
	}else goto err; 
err: 
	if(svr_sock>0) close(svr_sock); 
#else
	int svr_sock=tcp_svr_socket_preapre("0.0.0.0", 54188); 
	int name_max_len=128; 
	char *name=malloc(name_max_len+1);  
	if(!name) goto err; 
	if(svr_sock>0){
		struct sockaddr_in cli_addr; 
		socklen_t cli_addrlen; 
		int cli_sock=accept(svr_sock, (struct sockaddr *)&cli_addr, &cli_addrlen); 
		dbge("cli_sock(%d), addr(%s)", cli_sock, inet_ntoa(cli_addr.sin_addr)); 
		typedef struct cmd_t {
			uint32_t magic; 
			uint32_t type; 
			uint32_t len; 
		} cmd; 
		enum {
			CMD_NONE=0, 
			CMD_FILENAME, 
			CMD_FILEAPPEND, 
			CMD_END=255
		}; 
#define CMD_MAGIC 0x11223344
		if(cli_sock>0){
			while(1){
				cmd c;
				int len=recv(cli_sock, (void *)&c, sizeof(c), 0); 
				dbge("svr data(len(%d)) is coming..., c.magic(%08X)", len, c.magic); 
				if(ntohl(c.magic)!=CMD_MAGIC){
					dbge("clinet magic error(%08X)", ntohl(c.magic)); 
					close(cli_sock); 
					goto err; 
				}
				switch(ntohl(c.type)){
					case CMD_FILENAME: 
						{
							if(c.len>name_max_len){
								name=realloc((void *)name, name_max_len); 
								if(!name) goto err; 
							}
							int len=recv(cli_sock, (void *)name, sizeof(name), 0); 
							if(len!=c.len){
								close(cli_sock); 
								goto err; 
							}
							name[len]='\0'; 
							dbge("file name: %s", name); 
						}
						break; 
					case CMD_FILEAPPEND: 
						{
						}
						break; 
				}
			}
			dbge(); 
			close(cli_sock); 
		}else goto err; 
#undef CMD_MAGIC
	}else goto err; 
err: 
	if(svr_sock>0) close(svr_sock); 
	if(name) free(name); 
#endif
}
void tcp_test_cli(const char *ip_str){
	enter_n_exit(); 
#if 0
	int cli_sock=socket(AF_INET, SOCK_STREAM, 0); 
	if(cli_sock>0){
		int ret=0; 
		struct sockaddr_in svr_addr; 
		int optval=1; 
		ret=setsockopt(cli_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); 
		dbge("setsocketopt(ret(%d), optval(%d))", ret, optval); 
		optval=1; 
		ret=setsockopt(cli_sock, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)); 
		dbge("setsocketopt(ret(%d), optval(%d))", ret, optval); 
		svr_addr.sin_family=AF_INET; 
		svr_addr.sin_port=htons(54188); 
		svr_addr.sin_addr.s_addr=inet_addr(ip_str);
		int retval=connect(cli_sock, (struct sockaddr *)&svr_addr, sizeof(svr_addr)); 
		if(retval!=0) goto err; 
		typedef struct cmd_t {
			uint32_t magic; 
			uint32_t type; 
			uint32_t len; 
		} cmd; 
		enum {
			CMD_NONE=0, 
			CMD_FILENAME, 
			CMD_FILEAPPEND, 
			CMD_END=255
		}; 
		if(!retval){
			char name[]="obuspa.conf"; 
			cmd c; 
			c.magic=htonl(0x11223344); 
			c.type=htonl(CMD_FILENAME); 
			c.len=strlen(name); 
			send(cli_sock, (void *)&c, sizeof(c), 0); 
			send(cli_sock, (void *)name, c.len, 0); 
		}
		close(cli_sock); 
	}
#else
	int cli_sock=tcp_cli_socket_preapre(ip_str, 54188); 
	if(cli_sock>0){
		typedef struct cmd_t {
			uint32_t magic; 
			uint32_t type; 
			uint32_t len; 
		} cmd; 
		enum {
			CMD_NONE=0, 
			CMD_FILENAME, 
			CMD_FILEAPPEND, 
			CMD_END=255
		}; 
#define CMD_MAGIC 0x11223344
		char name[]="obuspa.conf"; 
		cmd c; 
		c.magic=htonl(CMD_MAGIC); 
		c.type=htonl(CMD_FILENAME); 
		c.len=strlen(name); 
		send(cli_sock, (void *)&c, sizeof(c), 0); 
		send(cli_sock, (void *)name, c.len, 0); 
#undef CMD_MAGIC
	}else goto err; 
err: 
	if(cli_sock>0) close(cli_sock); 
#endif
}
