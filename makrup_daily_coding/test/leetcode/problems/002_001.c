#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include "debug.h"
void dump(int *a, int n){
	printf("a[%d]:{", n); 
	for(int i=0; i<n; i++){
		printf("%d%s", a[i], i!=n-1?",":""); 
	}
	printf("}\n"); 
}
void swap(int *a, int *b){
	int c=*a; 
	*a=*b; 
	*b=c; 
}
struct ListNode {
	int val;
	struct ListNode *next; 
}; 
struct ListNode *createListNode(int *nums, int numsSize){
	if(!nums||numsSize<=0) return NULL; 
	struct ListNode *l=malloc(sizeof(struct ListNode)); 
	struct ListNode *pCurr=l; 
	if(l){
		l->val=nums[0]; 
		l->next=NULL; 
		for(int i=1; i<numsSize; i++){
			struct ListNode *append=malloc(sizeof(struct ListNode)); 
			if(append){
				append->next=NULL; 
				append->val=nums[i]; 
				pCurr->next=append; 
				pCurr=append; 
			}else{
				break; 
			}
		}
	}
	return l; 
}
void dumpListNode(struct ListNode *head){
	struct ListNode *pCurr=head; 
	while(pCurr){
		printf("(%d)%s", pCurr->val, pCurr->next?"->":""); 
		pCurr=pCurr->next; 
	}
	printf("\n"); 
}
#ifdef listnodedebug
#define listnodedbg(fmt,...) printf(fmt,##__VA_ARGS__)
#else
#define listnodedbg(fmt,...)
#endif
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode *pl1=l1, *pl2=l2; 
	struct ListNode *pSum=malloc(sizeof(struct ListNode)); 
	if(pSum){
		pSum->next=NULL; 
		pSum->val=pl1->val+pl2->val; 
		struct ListNode *pCurr=pSum; 
		int carry=pSum->val/10; 
		pSum->val=pSum->val%10; 
		pl1=pl1->next; 
		pl2=pl2->next; 
		while(pl1||pl2||carry){
			struct ListNode *pAppend=malloc(sizeof(struct ListNode)); 
			if(pAppend){
				pAppend->val=(pl1?pl1->val:0)+(pl2?pl2->val:0)+carry; 
				carry=pAppend->val/10; 
				pAppend->val=pAppend->val%10; 
				pAppend->next=NULL; 
				pCurr->next=pAppend; 
				pCurr=pAppend; 
				if(pl1) pl1=pl1->next; 
				if(pl2) pl2=pl2->next; 
			}else break; 
		}
	}
	return pSum; 
}
#if 0
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	int num1=0, num2=0; 
	struct ListNode *pCurr=l1; 
	while(pCurr){
		num1=10*num1+pCurr->val; 
		pCurr=pCurr->next; 
	}
	listnodedbg("num1(%d)\n", num1); 
	pCurr=l2; 
	while(pCurr){
		num2=10*num2+pCurr->val; 
		pCurr=pCurr->next; 
	}
	listnodedbg("num2(%d)\n", num2); 
	int sum=num1+num2; 
	listnodedbg("sum(%d)\n", sum); 
	struct ListNode *pSum=malloc(sizeof(struct ListNode)); 
	if(pSum){
		pSum->next=NULL; 
		pSum->val=sum%10; 
		sum=sum/10; 
		while(sum){
			struct ListNode *pPrepend=malloc(sizeof(struct ListNode)); 
			if(pPrepend){
				pPrepend->next=pSum; 
				pPrepend->val=sum%10; 
				pSum=pPrepend; 
			}else break; 
			sum=sum/10; 
		}
	}
	return pSum;     
}
#endif
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	{
		struct ListNode *l1=createListNode((int[]){2,4,3}, 3); 
		struct ListNode *l2=createListNode((int[]){5,6,4}, 3); 
		printf("l1: "); 
		dumpListNode(l1); 
		printf("l2: "); 
		dumpListNode(l2); 
		struct ListNode *sum=addTwoNumbers(l1, l2); 
		printf("sum: "); 
		dumpListNode(sum); 
	}
	{
		struct ListNode l1={.val=2,.next=&((struct ListNode){.val=4, .next=&((struct ListNode){.val=3, .next=NULL})})}; 
		struct ListNode l2={.val=5,.next=&((struct ListNode){.val=6, .next=&((struct ListNode){.val=4, .next=NULL})})}; 
#if 0
		struct ListNode *l1=createListNode((int[]){2,4,3}, 3); 
		struct ListNode *l2=createListNode((int[]){5,6,4}, 3); 
#endif
		printf("l1: "); 
		dumpListNode(&l1); 
		printf("l2: "); 
		dumpListNode(&l2); 
		struct ListNode *sum=addTwoNumbers(&l1, &l2); 
		printf("sum: "); 
		dumpListNode(sum); 
	}
	{
		struct ListNode l1={.val=9,.next=&((struct ListNode){.val=9, .next=&((struct ListNode){.val=9, .next=&((struct ListNode){.val=9, .next=&((struct ListNode){.val=9, .next=&((struct ListNode){.val=9, .next=&((struct ListNode){.val=9, .next=NULL})})})})})})}; 
		struct ListNode l2={.val=9,.next=&((struct ListNode){.val=9, .next=&((struct ListNode){.val=9, .next=&((struct ListNode){.val=9, .next=NULL})})})}; 
#if 0
		struct ListNode *l1=createListNode((int[]){2,4,3}, 3); 
		struct ListNode *l2=createListNode((int[]){5,6,4}, 3); 
#endif
		printf("l1: "); 
		dumpListNode(&l1); 
		printf("l2: "); 
		dumpListNode(&l2); 
		struct ListNode *sum=addTwoNumbers(&l1, &l2); 
		printf("sum: "); 
		dumpListNode(sum); 
	}
	return 0; 
}
