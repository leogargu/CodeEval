#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <vector>


/*Challenge description:
https://www.codeeval.com/open_challenges/5/
*/

/* It is assumed that in the input, once an element is repeated, the sequence continues periodically. E.g.
2 0 6 3 1 6 3 1 6 3 1
3 4 8 0 11 9 7 2 5 6 10 1 49 49 49 49
1 2 3 1 2 3 1 2 3
*/

/* Print (to stdout) vector elements from position a to b inclusive */
template<class T>
void print_vector(const std::vector<T>& v, int a, int b){
	/* Health check */
	const int size=v.size();
	assert( a>=0 && b<size );
	
	/* Avoiding trailing space */
	for(int i=a; i<b; i++){
		std::cout << v[i] << " ";
	}
	std::cout << v[b] << std::endl;
}


/* Print a vector to stdout */
template<class T>
void print_vector(const std::vector<T>& v){
	const int size=v.size();
	
	print_vector(v, 0, size-1);

}

/* Convert string of numbers to vector */
template<class T>
void string_to_vector(const std::string& line, std::vector<T>& str_vec){	
	str_vec.clear(); //back to size 0
	
	std::stringstream ss;
	ss.str(line);
	T number;
	
	while(ss){
		ss >> number;
		str_vec.push_back(number);
	}
	
}

/* Find position of element in the vector, returns -1 if element is not in the vector*/
template<class T>
int element_position(T element, std::vector<T> v){
	const int size = v.size();
	
	for (int i=0; i<size; i++){
		if( element == v[i] ){
			return i;
		}
	}
	return -1;
}

/* Cycle finder function   */
/* Input: vector v  	   */
/* Output: vector cycle    */
template<class T>
void find_cycle(const std::vector<T>& v, std::vector<T>& cycle){
	cycle.clear();
	const int size=v.size();
	int pos;
	
	for(int i=0;i<size;i++){
		pos = element_position(v[i],cycle); 
		if( pos == -1 ){
			cycle.push_back(v[i]);
		}else{
			print_vector(cycle, pos, cycle.size()-1);
			break;
		}
	}
}


/* Cycle finder main program */
int main(int argc, char ** argv){
	std::ifstream fs;
	fs.open(argv[1]);
	if( !fs.is_open() ){
		return 1;
	}
	
	std::string line;
	std::vector<int> str_vec; //empty vector of ints
	std::vector<int> cycle;
	
	while( std::getline(fs,line) ){
		string_to_vector(line, str_vec);
		find_cycle(str_vec,cycle);
	}
	
	fs.close();
	return 0;
}