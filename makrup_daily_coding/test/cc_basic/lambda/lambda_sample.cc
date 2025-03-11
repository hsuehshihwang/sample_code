#include <iostream>
using namespace std; 
int main(int argc, char *argv[]){
	cout << __FUNCTION__ << "@" << __LINE__ << ":" << endl; 
	int v=99; 
	auto f=[&](int _v){
		printf("v(%d), _v(%d)\n", v, _v); 
		return _v+1; 
	}; 
	printf("f(): %d\n", f(101)); 
	return 0; 
}
