#include <iostream>
#include <fstream>
#include <string>
#include<assert.h>

/*Challenge description:
https://www.codeeval.com/open_challenges/74/
*/

/* Format of input file is not checked */

int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	std::string line;
	int num;
	int five,three,one; //number of each type of coin needed
	
	while( std::getline(ifs,line) ){
		num = std::stoi(line);
		five = num/5;		  //integer division
		three = (num - 5*five)/3; //integer division
		one = num - five *5 - three*3;
		
		assert(5*five+3*three+one==num);
		std::cout << five + three + one << std::endl;
	}
	
	
	ifs.close();
	return 0;
}
