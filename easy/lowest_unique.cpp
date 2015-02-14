#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <assert.h>

/*Challenge description: 
https://www.codeeval.com/open_challenges/103/
*/

// Note: format of input file is not checked.


//sorting function to be used with <algorithm>'s sort
bool sort_fun(int i, int j){
	return i<j;
}

//prints vector to stdout
template<class T>
void print_vector(const std::vector<T>& v){
	typename std::vector<T>::const_iterator it=v.begin();
	std::cout << *it ;
	for(it=v.begin()+1; it != v.end(); it++){
		std::cout << ","<< *it ;
	}
	std::cout << std::endl;
}


//returns -1 if nnumber is not in vector, or the position of number in teh vector otherwise
template<class T>
int find_pos(T number, const std::vector<T>& v){
	typename std::vector<T>::const_iterator it;
	for(it=v.begin(); it!=v.end(); it++){
		if( number == *it){
			return it-v.begin();
		}
	}
	return -1;
}

//main program
int main(int argc , char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	std::string line;
	int number, counter=1, winner;
	bool found;
	std::vector<int> v;
	std::vector<int>::iterator it;
	std::stringstream ss;
	
	while(std::getline(ifs,line)){
		v.clear();
		ss.clear();
		ss.str(line);
		while(ss >> number){
			v.push_back(number);
		}
		//now we have loaded all the numbers
		std::vector<int> v_sorted(v);
		std::sort(v_sorted.begin(),v_sorted.end(),sort_fun);
				
		it=v_sorted.begin();
		number = *it;
		found = false;
		while( it != v_sorted.end() ){
			it++;
			if(*it == number){
				counter++;
			}else if(counter==1){
				winner = find_pos(number,v)+1;
				assert(winner>0);
				std::cout << winner << std::endl;
				found = true;
				break;
			}else{
				counter = 1;
				number = *it;
			}
		}
		if(!found){
			std::cout << 0 << std::endl;
		}
		
		
	}
	
	ifs.close();
	return 0;
}
