#include "tcp_svr_cli.h"
int tcp_svr_socket_preapre(const char *ip_str, int port){
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
		svr_addr.sin_port=htons(port); 
		svr_addr.sin_addr.s_addr=inet_addr(ip_str);
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
	}else goto err; 
	return svr_sock; 
err: 
	if(svr_sock>0) close(svr_sock); 
	return -1; 
}
int tcp_cli_socket_preapre(const char *ip_str, int port){
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
		svr_addr.sin_port=htons(port); 
		svr_addr.sin_addr.s_addr=inet_addr(ip_str);
		ret=connect(cli_sock, (struct sockaddr *)&svr_addr, sizeof(svr_addr)); 
		if(ret!=0) goto err; 
	}
	return cli_sock; 
err: 
	return -1; 
}
