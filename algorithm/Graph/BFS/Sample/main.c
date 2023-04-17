
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "debug.h"
#include "vertex.h"
#include "queue.h"
#include "bfs.h"
#include "dfs.h"

int main(int argc, char *argv[]){
	// vertexTest(); 
	bfsTest(); 
	// dfsTest(); 
	// queueTest(); 
	// stackTest(); 
    exit(EXIT_SUCCESS);
}

