#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/*Challenge description:
https://www.codeeval.com/open_challenges/24/
*/
int main(int argc, char ** argv){
	std::ifstream fstream;
	fstream.open(argv[1]);
	std::string line;
	std::stringstream ss;
	int digit;
	int sum = 0;
	
	while( std::getline(fstream,line) ){
		ss.clear();
		ss.str(line);
		ss>>digit;
		sum +=digit;
	}
	
	std::cout << sum << std::endl;
	
	fstream.close();
	return 0;
}