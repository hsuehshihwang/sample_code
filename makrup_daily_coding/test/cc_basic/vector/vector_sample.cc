#include <iostream>
#include <vector>
using namespace std; 
int main(int argc, char *argv[]){
	cout << __FUNCTION__ << "@" << __LINE__ << ":" << endl; 
	vector<int> v_int={9,7,3,2,1,5,9,8,6}; 
	cout << "v_int[" << v_int.size() << "]: {"; 
	for(vector<int>::iterator it=v_int.begin(); it!=v_int.end(); it++){
		cout << *it << (it!=(v_int.end()-1)?",":""); 
	}
	cout << "}" << endl; 
	return 0; 
}
