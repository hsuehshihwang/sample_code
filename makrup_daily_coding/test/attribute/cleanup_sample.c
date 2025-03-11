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
	void cleanup_func(int *_x){
		printf("%s@%d: _x(%d)\n", __FUNCTION__, __LINE__, *_x); 
	}
	int __attribute__((cleanup(cleanup_func))) x=999; 
	return 0; 
}
