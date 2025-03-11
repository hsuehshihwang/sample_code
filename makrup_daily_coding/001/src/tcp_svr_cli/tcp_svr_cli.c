#include "tcp_svr_cli.h"
#define TCP_SVR_SELECT_MAX_CLI 10
void tcp_svr_select(int argc, char *argv[]){
	enter_n_exit(); 
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
		int retval=0; 
		struct timeval tv; 
		tv.tv_sec=5; 
		tv.tv_usec=0; 
		fd_set rfds;  
		int max_sock=svr_sock; 
		int cli_sock[TCP_SVR_SELECT_MAX_CLI]={0}; 
		memset(cli_sock, 0, sizeof(cli_sock)); 
		while(1){
			FD_ZERO(&rfds); 
			FD_SET(svr_sock, &rfds); 
			for(int i=0; i<TCP_SVR_SELECT_MAX_CLI; i++){
				if(cli_sock[i]>0){
					FD_SET(cli_sock[i], &rfds); 
					if(cli_sock[i]>max_sock) max_sock=cli_sock[i]; 
				}
			}
			retval=select(max_sock+1, &rfds, NULL, NULL, &tv); 
			if(retval==-1){
				perror("select error"); 
			}else if(retval){
				if(FD_ISSET(svr_sock, &rfds)){
					struct sockaddr_in cli_addr; 
					socklen_t cli_addrlen; 
					int new_cli_sock=accept(svr_sock, (struct sockaddr *)&cli_addr, &cli_addrlen); 
					if(new_cli_sock<0){
						perror("accept error"); 
						continue; 
					}
					dbge("new client: new_cli(%d), addr(%s), port(%d)", new_cli_sock, inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port)); 
					for(int i=0; i<TCP_SVR_SELECT_MAX_CLI; i++){
						if(cli_sock[i]==0){
							cli_sock[i]=new_cli_sock; 
							break; 
						}
					}
				}
				for(int i=0; i<TCP_SVR_SELECT_MAX_CLI; i++){
					int bytes_available=0; 
					if(FD_ISSET(cli_sock[i], &rfds)){
						if(ioctl(cli_sock[i], FIONREAD, &bytes_available)<0){
							perror("ioctl(FIONREAD) error"); 
							close(cli_sock[i]); 
							cli_sock[i]=0; 
							continue; 
						}
					}
					if(bytes_available==0){
						close(cli_sock[i]); 
						cli_sock[i]=0; 
					}else if(bytes_available>0){
#if 0
						typedef struct cmd_t {
						} cmd; 
						uint8_t data_buf[256]={0}; 
						int data_len=0; 
						int data_offset=0; 
						while(1){
							data_len=recv(cli_sock[i], data_buf+data_offset, sizeof(data_buf)-1-data_offset, NULL); 
							// check data and offset data, if each data chunk is under 128 bytes
							usleep(10); 
						}
#endif
					}
				}
			}else{
				dbge("5 secs timeout!!"); 
				break; 
			}
		}
		for(int i=0; i<TCP_SVR_SELECT_MAX_CLI; i++){
			if(cli_sock[i]>0){
				close(cli_sock[i]); 
			}
		}
		close(svr_sock); 
	}else goto err; 
err: 
	if(svr_sock>0) close(svr_sock); 
}
void tcp_svr(int argc, char *argv[]){
	enter_n_exit(); 
	tcp_svr_select(argc, argv); 
}
void tcp_cli(const char *ip_str){
	enter_n_exit(); 
}
int tcp_svr_cli_main(int argc, char **argv){
	if(argc>1){
		enter_n_exit(); 
		if(!strcmp(argv[1], "svr")){
			tcp_svr(argc-1, argv+1); 
		}else if(!strcmp(argv[1], "cli")){
			tcp_cli(argc>2?argv[2]:"127.0.0.1"); 
		}else if(!strcmp(argv[1], "test")){
			if(argv[2]&&!strcmp(argv[2], "svr")){
				tcp_test_svr(); 
			}else if(argv[2]&&!strcmp(argv[2], "cli")){
				tcp_test_cli(argv[3]?argv[3]:"127.0.0.1"); 
			}else goto err; 
		}
		return 0; 
	}
err: 
	tcp_svr_cli_usage(argv[0]); 
	return 0; 
}
