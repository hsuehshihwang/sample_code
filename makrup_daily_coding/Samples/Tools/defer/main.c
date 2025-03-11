#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

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

typedef void (*defer_func)(void); 

typedef struct defer_node {
	defer_func func; 
	struct defer_node *next; 
} defer_node; 


typedef struct defer_list {
	defer_node *head; 
} defer_list; 


void defer_init(defer_list *list){
	list->head=NULL; 
}

void defer_add(defer_list *list, defer_func func){
	if(list){
		defer_node *node=malloc(sizeof(defer_node)); 
		if(node){
			node->next=NULL; 
			node->func=func; 
			if(!list->head){
				list->head=node; 
			}else{
				node->next=list->head; 
				list->head=node; 
			}
		}
	}
}

void defer_exec(defer_list *list){
	if(list){
		defer_node *node=list->head; 
		while(node){
			node->func(); 
			node=node->next; 
		}
	}
}

void defer_destroy(defer_list *list){
	if(list){
		defer_node *node=list->head, *node_temp=NULL; 
		while(node){
			node_temp=node->next; 
			free(node); 
			node=node_temp; 
		}
		list->head=NULL; 
	}
}


#define DEFER_INIT() \
	defer_list __defer_list; \
	defer_init(&__defer_list); 


#define DEFER_ADD(name,func) \
	func \
	defer_add(&__defer_list,name); 

#define DEFER_RUN() \
	defer_exec(&__defer_list); 

#define DEFER_DESTROY() \
	defer_destroy(&__defer_list); 

void test001(void){
	DEFER_INIT(); 
	int sock_fd=socket(AF_INET, SOCK_STREAM, 0); 
	DEFER_ADD(cleanup1, void cleanup1(void){
		dbge("close(sock_fd(%d))", sock_fd); 
		if(sock_fd>0) close(sock_fd); 
	}); 
	if(!(sock_fd>0)) goto err; 
	FILE *fp=fopen("Makefile", "r+"); 
	DEFER_ADD(cleanup2, void cleanup2(void){
		dbge("fclose(fp)"); 
		if(fp) fclose(fp); 
	}); 
	if(!fp) goto err; 
err: 
	DEFER_RUN(); 
	DEFER_DESTROY(); 
}

int main(int argc, char *argv[]){
	dbge(); 
	test001(); 
    exit(EXIT_SUCCESS);
}

