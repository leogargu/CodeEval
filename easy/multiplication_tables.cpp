#include <iostream>
#include <iomanip>

/*Challenge description: 
https://www.codeeval.com/open_challenges/23/
*/
int main(int argc, char ** argv){
	
	int max_num = 12;
	
	for(int i=1; i<=max_num; i++){
		for(int j=1;j<=max_num;j++){
			std::cout << i*j;
			if(j!=max_num){
				std::cout <<  std::setw(4);
			}
		}
		std::cout << std::endl;
	}
	
	return 0;
}