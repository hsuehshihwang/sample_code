#include "main.h"
#include "defer.h"

int TCPSvrInit(int *psock){
	defer d; 
	d.add([&](){
		cout << "defer func 1" << endl; 
	}); 
	d.add([&](){
		cout << "defer func 2" << endl; 
	}); 
	d.add([&](){
		cout << "defer func 3" << endl; 
	}); 
	return 0; 
}
void TCPSvrTest(void){
	int svr_sock=0; 
	TCPSvrInit(&svr_sock); 
}
int main(void){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	dbge(); 
	debug_test(); 
	vector_test(); 
	SYSTEM_test(); 
	TCPSvrTest(); 
	return 0; 
}
