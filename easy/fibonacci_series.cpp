#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/*Challenge description:
https://www.codeeval.com/open_challenges/22/
*/

int fibonacci(int N){
	if(N==0){
		return 0;
	}else if(N==1){
		return 1;
	}else{
		return fibonacci(N-1)+fibonacci(N-2);																																																						
	}
}



int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}																	
	
	std::string line;
	int n;
	std::stringstream ss;
	
	while(std::getline(ifs,line)){
		ss.clear();
		ss.str(line);
		ss >> n;
		
		std::cout << fibonacci(n)<< std::endl;;
	}
	
	ifs.close();
	return 0;
}