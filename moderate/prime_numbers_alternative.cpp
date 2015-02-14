#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

/*Challenge description: 
https://www.codeeval.com/open_challenges/46/
*/

// Note: format of input file is not checked.

template<class T>
void print_vector(const std::vector<T>& v){
	typename std::vector<T>::const_iterator it=v.begin();
	std::cout << *it ;
	for(it=v.begin()+1; it != v.end(); it++){
		std::cout << ","<< *it ;
	}
	std::cout << std::endl;
}


int main(int argc , char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	std::string line;
	long max_num;
	std::vector<int> primes;
	
	std::vector<int>::iterator it;
	bool is_prime;
	std::stringstream ss;
	
	while(std::getline(ifs,line)){
		ss.clear();
		ss.str(line);
		ss >> max_num;
		
		primes.clear();
		primes.push_back(2);
		long last_int;
		for(long i=3; i<max_num; i++){
			is_prime=true;
			last_int = ceil(sqrt(i));
			for(it=primes.begin(); it!=primes.end(); it++){
				if( i % *it == 0 ){
					is_prime=false;
					break;
				}
				if( *it > last_int ){
					break;
				}
				
			}
			if(is_prime){
				primes.push_back(i);
			}//else do nothing
			
		}
		
		print_vector(primes);
		
	}
	
	ifs.close();
	return 0;
}
