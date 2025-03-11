#include "main.h"
int main(int argc, char *argv[]){
	// test_main(argc, argv); 
	// debug_main(argc, argv); 
	// tcp_svr_cli_main(argc, argv); 
	int sock=socket(AF_INET, SOCK_STREAM, 0); 
	if(sock>0){
		int ret=0; 
		socklen_t opt=1; 
		if((ret=setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt)))!=0) goto err; 
		struct sockaddr_in addr; 
		addr.sin_family=AF_INET; 
		addr.sin_port=htons(54188); 
		addr.sin_addr.s_addr=inet_addr("0.0.0.0"); 
		ret=bind(sock, (const struct sockaddr *)&addr, sizeof(addr)); 
	}else goto err; 
err: 
	if(sock>0) close(sock); 
	return 0; 
}
