#include <iostream>
#include "test.cc.h"
using namespace std; 
// one liner for enter and exit prompt
#undef __enter_n_exit__
#define __enter_n_exit__() class __enter_n_exit__ { public: __enter_n_exit__(const char *_n){ n=_n; printf("Enter(%s)\n", _n); } ~__enter_n_exit__(){ printf("Exit(%s)\n", n); } private:  const char *n; }; __enter_n_exit__ __ene__(__FUNCTION__); 
void child(){
	__enter_n_exit__(); 
}
#undef __enter_n_exit__
#define __enter_n_exit__() \
	class __enter_n_exit__ { \
		public: \
			__enter_n_exit__(const char *_n){ n=_n; printf("Enter(%s)\n", _n); } \
			~__enter_n_exit__(){ printf("Exit(%s)\n", n); } \
		private: \
			 const char *n; \
	}; \
	__enter_n_exit__ __ene__(__FUNCTION__); 
void parent(){
	__enter_n_exit__(); 
	child(); 
}
#undef __enter_n_exit__
#define __enter_n_exit__() \
	class __enter_n_exit__ { \
		public: \
			__enter_n_exit__(const char *_n){ n=_n; printf("Enter(%s)\n", _n); } \
			~__enter_n_exit__(){ printf("Exit(%s)\n", n); } \
		private: \
			 const char *n; \
	}; \
	__enter_n_exit__ __ene__(__FUNCTION__); 
int main(int argc, char *argv[]){
	__enter_n_exit__(); 
	cout << __FUNCTION__ << "@" << __LINE__ << ":" << endl; 
	parent(); 
	return 0; 
}
