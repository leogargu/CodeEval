#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/* Challenge description:
https://www.codeeval.com/open_challenges/100/
*/


int main(int argc, char ** argv){
	std::ifstream file;
	file.open(argv[1]);
	if(!file.is_open()){
		return 1;
	}
	
	std::stringstream ss;
	std::string line;
	int number, is_even;
	

	while( std::getline(file,line) ){
		ss.clear();
		ss.str(line);
		ss >> number;
		
		if(number%2){
			is_even=0;
		}else{
			is_even=1;
		}
		std::cout << is_even << std::endl;
	}
	
	file.close();
	return 0;
}