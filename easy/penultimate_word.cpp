#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/* Challenge description: 
https://www.codeeval.com/open_challenges/92/
*/

int main(int argc , char ** argv ){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	std::string line, word, last_word;
	std::string penultimate_word="";
	std::string::reverse_iterator it;
	std::stringstream ss;
	
	while(std::getline(ifs, line)){
		ss.clear();
		ss.str(line);
		penultimate_word="";
		last_word="";
		while ( ss>> word ){
			penultimate_word=last_word;
			last_word=word;
		}
		
		std::cout << penultimate_word<< std::endl;
	}
	
	//clean up
	ifs.close();
	return 0;
}