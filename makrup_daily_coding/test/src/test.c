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
	printf("%s@%d: 00666(%x)\n", __FUNCTION__, __LINE__, 00666); 
	char *data=strdup("cmd_append/file\x1Ralph: hello world!!"); 
	if(data){
		printf("%s@%d: data(%s)\n", __FUNCTION__, __LINE__, strstr(data, "\x1")+1); 
		free(data); 
		data=NULL; 
	}
	data=strdup("Ralph is a good boy!!\nElly is a good girl!!\n"); 
	if(data){
		printf("%s@%d: data(%s)\n", __FUNCTION__, __LINE__, data); 
		printf("%s@%d: strspn(Ralph): %ld\n", __FUNCTION__, __LINE__, strspn(data, "Ralph")); 
		printf("%s@%d: strcspn(\\n): %ld\n", __FUNCTION__, __LINE__, strcspn(data, "\n")); 
		printf("%s@%d: strcspn(boy): %ld\n", __FUNCTION__, __LINE__, strcspn(data, "boy")); 
		free(data); 
		data=NULL; 
	}
	return 0; 
}
