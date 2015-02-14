#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> //sort
#include <vector> // needed for sort


/*Challenge description: 
https://www.codeeval.com/open_challenges/41/
*/

bool myfun(int i, int j){
	return i<j;
}


template <class T>
void print_vector(std::vector<T> v){
	typename std::vector<T>::iterator it;
	for(it=v.begin(); it!=v.end(); it++){
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}


template<class T>
void print_array(T * v, int size){
	for(int i=0; i<size; i++){
		std::cout << v[i]<< " ";
	}
	std::cout << std::endl;
}

int main(int argc , char ** argv ){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	std::string line, num_str;
	std::stringstream ss;
	int size, digit;
	std::size_t comma1=0, comma2=0;
	
	std::vector<int> v;
	
	while(std::getline(ifs, line)){
		ss.clear();
		ss.str(line);
		ss >> size;
		
		ss>>num_str;
		num_str.erase(0,1);//remove the semicolon
			
		std::vector<int> v(size,0);
		
		for(int i=0; i<size; i++){
			comma2 = num_str.find(",", comma1);
			v[i] = std::stoi(num_str.substr(comma1, comma2-comma1));
			comma1=comma2+1;
		}
		
		std::sort(v.begin(), v.end(), myfun);
		
		digit = v[0];
		for(int i=1; i<size; i++){
			if(digit==v[i]){
				std::cout << digit << std::endl;
				break;
			}else{
				digit = v[i];
			}
		}
		
	}
	
	//clean up
	ifs.close();
	return 0;
}
