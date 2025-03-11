#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <libgen.h>

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 

#define REPEAT_5(C) C C C C C
#define REPEAT_10(C) REPEAT_5(C) REPEAT_5(C)
#define REPEAT_20(C) REPEAT_10(C) REPEAT_10(C)
#define REPEAT_40(C) REPEAT_20(C) REPEAT_20(C)
#define REPEAT_80(C) REPEAT_40(C) REPEAT_40(C)

#define REPEAT(C,n) REPEAT_##n(C)

#define FUNC_BAR REPEAT("=",20)

#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
		fflush(stdout); \
    } while(0); 

int main(int argc, char *argv[]){
	dbge(); 
	int cli_sock=socket(AF_INET, SOCK_STREAM, 0); 
	if(cli_sock>0){
		int optval=1; 
		setsockopt(cli_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); 
		struct sockaddr_in svr_addr; 
		svr_addr.sin_family=AF_INET; 
		svr_addr.sin_port=htons(54188); 
		svr_addr.sin_addr.s_addr=inet_addr("192.168.2.125");  // INADDR_ANY
		connect(cli_sock, (const struct sockaddr *)&svr_addr, sizeof(svr_addr)); 
		char buf[]="Hi, I'm client!!"; 
		send(cli_sock, buf, sizeof(buf), 0); 
		close(cli_sock); 
	}
    exit(EXIT_SUCCESS);
}

