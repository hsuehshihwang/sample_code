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
	typedef struct unpacked {
		char name[10]; 
		union {
			int i; 
			char c[20]; 
		}; 
	} unpacked; 
	// typedef struct __attribute__((packed)) packed {
	typedef struct packed {
		char name[10]; 
		union {
			int i; 
			char c[20]; 
		}; 
	} __attribute__((packed)) packed ; 
	printf("%s@%d: sizeof(unpacked): %ld\n", __FUNCTION__, __LINE__, sizeof(unpacked)); 
	printf("%s@%d: sizeof(packed): %ld\n", __FUNCTION__, __LINE__, sizeof(packed)); 
	return 0; 
}
