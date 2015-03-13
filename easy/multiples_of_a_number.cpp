#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

/*Challenge description:
https://www.codeeval.com/open_challenges/18/
*/

int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	std::string line, word;
	int comma;
	int x, n, m;
	
	while(std::getline(ifs, line)){
		comma = line.find(',');
		word = line.substr(0,comma);
		x = atoi(word.c_str());
		word = line.substr(comma+1,std::string::npos);
		n = atoi(word.c_str());
		m=n;
		while(m<x){
			m+=n;
		}
		std::cout << m << std::endl;

	}
	
	
	ifs.close();
	return 0;

}