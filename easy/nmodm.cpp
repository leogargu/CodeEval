#include <iostream>
#include <fstream>
#include <string>


/*Challenge description: 
https://www.codeeval.com/open_challenges/62/
*/

int my_mod(int n, int m){
	return n-m*(n/m);
}


int main(int argc , char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	std::string line;
	std::size_t comma;

	int a,b;
	
	while(std::getline(ifs,line)){
		comma = line.find(',');
		a = std::stoi(line.substr(0,comma));
		b = std::stoi(line.substr(comma+1));
		
		
		std::cout << my_mod(a,b) << std::endl;

	}
	
	
	ifs.close();
	return 0;
}
