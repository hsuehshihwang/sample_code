#include <stdlib.h>
#include "defer.h"
void defer_init(defer_list *list){
	if(list){
		list->head=NULL; 
	} 
}
void defer_add(defer_list *list, defer_func func){
	if(list){
		defer_node *node=malloc(sizeof(defer_node)); 
		if(node){
			// FILO
			node->next=list->head; 
			node->func=func; 
			list->head=node; 
		}
	}
}
void defer_cleanup_function(defer_list *list){
	if(list){
		defer_node *node=list->head; 
		defer_node *node_next=NULL; 
		while(node){
			node_next=node->next; 
			node->func(); 
			free(node); 
			node=node_next; 
		}
	}
}
