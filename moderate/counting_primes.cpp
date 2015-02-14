#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

/*Challenge description: 
https://www.codeeval.com/open_challenges/63/
*/


bool is_prime(int a){
	if(a<=1){
		return false;
	}
	for(int i=2; i<a; i++){
		if(a%i==0){
			return false;
		}
	}
	
	return true;
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
	int counter =0;
	
	while(std::getline(ifs,line)){
		comma = line.find(',');
		a = std::stoi(line.substr(0,comma));
		b = std::stoi(line.substr(comma+1));
		
		counter =0;
		for(int i=a; i<=b; i++){
			if(is_prime(i)){
				counter++;
			}
		}
		
		std::cout << counter << std::endl;
	}
	
	
	ifs.close();
	return 0;
}