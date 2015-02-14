#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>

/* Challenge description: 
https://www.codeeval.com/open_challenges/40/
*/

/* Each line in the input file should contain only one positive integer (not checked) */
/* Self-describing numbers only make sense if they have up to 10 digits */



/* Reverses elements in input vector */
template<class T>
void reverse_vec(std::vector<T>& a){
	std::vector<T> b(a);
	const int size=a.size();
	for(int i=0; i<size; i++){
		a[i]=b[size-1-i];
	}
}


/* Breaks an integer into its digits */
void int_to_digits(int x, std::vector<int>& digits){
	int y;
	digits.clear();
	while( x > 0 ){
		y = x/10;
		digits.push_back( x-y*10) ;
		x = y;
	}
	reverse_vec(digits);
}


/* Print (to stdout) vector elements from position a to b inclusive */
template<class T>
void print_vector(const std::vector<T>& v, int a, int b){
	/* Health check */
	const int size=v.size();
	assert( a>=0 && b<size );
	
	/* Avoiding trailing space */
	for(int i=a; i<b; i++){
		std::cout << v[i] << " ";
	}
	std::cout << v[b] << std::endl;
}


/* Print a vector to stdout */
template<class T>
void print_vector(const std::vector<T>& v){
	const int size=v.size();
	
	print_vector(v, 0, size-1);

}


/* Get number of each digit in the integer */
void int_stats(const std::vector<int>& digits, std::vector<int>& stats){
	const int size=digits.size();
	assert(stats.size()==10);
	
	//use <algorithm> std::fill, or:	
	for(int i=0; i<10;i++){
		stats[i]=0;
	}
	
	//gather stats
	for(int i=0;i<size;i++){
		assert(digits[i]<=9 && digits[i]>=0);
		stats[digits[i]]+=1;
	}
	
}




int main(int argc, char ** argv){
	std::ifstream file;
	file.open(argv[1]);
	if(!file.is_open()){
		return 1;
	}
	
	std::stringstream ss;
	std::string line;
	int number, self_describing;
	
	std::vector<int> digits;
	std::vector<int> stats(10,0);

	while( std::getline(file,line) ){
		ss.clear();
		ss.str(line);
		ss >> number;
		int_to_digits(number, digits);
		int_stats(digits,stats);
		self_describing = 1;
		for(int i=0; i<digits.size(); i++){
			if( digits[i]!=stats[i]){
				self_describing = 0;
				break;
			}
		}
		if(self_describing){
			std::cout << "1" << std::endl;
		}else{
			std::cout << "0" << std::endl;
		}
	}
	
	file.close();
	return 0;
}