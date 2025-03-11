#include <iostream>
#include <vector>
#include "debug.h"

using namespace std; 

void vector_test(void){
	dbge(); 
	vector<int> v={9,7,3,2,1,5};
	v.insert(v.end(), {6,8,4}); 
	cout << "v: "; 
	for(vector<int>::iterator it=v.begin(); it<v.end(); it++){
		cout << *it << (it==(v.end()-1)?"":","); 
	}
	cout << endl; 
}
