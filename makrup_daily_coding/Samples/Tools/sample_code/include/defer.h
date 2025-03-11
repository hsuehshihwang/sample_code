#ifndef __defer_h__
#define __defer_h__

#include <iostream>
#include <stack>
#include <functional>

using namespace std; 
class defer {
public: 
	defer(){}
	// defer(function<void(void)> f){ functions.push(f); }
#if 0
	void add(function<void(void)> f){
		functions.push(f); 
	}
#else
	void add(function<void(void)> f);
#endif
	~defer(){
		while(functions.size()){
			functions.top()(); 
			functions.pop(); 
		}
	}
private: 
	stack <function<void(void)>> functions; 
}; 

#endif /*__defer_h__*/
