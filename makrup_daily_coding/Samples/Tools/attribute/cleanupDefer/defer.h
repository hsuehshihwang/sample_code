#ifndef __defer_h__
#define __defer_h__
typedef void (*defer_func)(void); 
typedef struct defer_node {
	defer_func func; 
	struct defer_node *next; 
} defer_node; 
typedef struct defer_list {
	defer_node *head; 
} defer_list; 
void defer_init(defer_list *list);
void defer_add(defer_list *list, defer_func func); 
void defer_cleanup_function(defer_list *list); 
#define DEFER_INIT() \
	defer_list __attribute__((cleanup(defer_cleanup_function))) __dlist; \
	defer_init(&__dlist); 
#define DEFER_ADD(name,code) \
	code \
	defer_add(&__dlist,name); 
#endif /*__defer_h__*/
