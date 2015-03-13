#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

/*Challenge description
https://www.codeeval.com/open_challenges/47/
*/

//prints elements of a vector
template<class T>
void print(std::vector<T> v){
	typename std::vector<T>::iterator it;
	for(it=v.begin(); it!=v.end(); it++){
		std::cout << *it <<" ";
	}
	std::cout <<std::endl;
}


//prints elements of a vector, in reverse order
template<class T>
void rprint(std::vector<T> v){
	typename std::vector<T>::reverse_iterator rit;
	for(rit=v.rbegin(); rit!=v.rend(); rit++){
		std::cout << *rit <<" ";
	}
	std::cout <<std::endl;
}



//Returns 1 is the number a is palindrome, 0 otherwise	
int is_palindrome(int a){
	//split num into digits (stored in reverse order)
	std::vector<int> digits;
	
	while(a!=0){
		digits.push_back(a-10*(a/10));
		a=a/10;
	}

	//check palindrome
	int length = digits.size();
	
	for(int i=0;i<length; i++){
		if(digits[i]!=digits[length-i-1]){
			return 0;	
		}
	}
	return 1;
}



/*Returns 1 if the range represented by [palin[L],palin[R]] has an even number of palindromes, 0 otherwise.
Note that the actual range is [L+l,R+l] where l is the original L value in the input file
*/
int is_palindromic_range(int L, int R, std::vector<int> palin){
	int num=0;//number of palindromes in the interval represented by [palin[L],palin[R]] -->note offset by L
	for(int i=L; i<=R; i++){
		num+=palin[i];//0 or 1
	}
	if(num%2==0){//even number of palindromes
		return 1;
	}//else, return 0
	return 0;
}

//main program
int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	std::string line;
	std::stringstream ss;
	int L,R;
	
	while(std::getline(ifs,line)){
		ss.clear();
		ss.str(line);
		ss >> L;
		ss >> R;
		
		//store palindrome status of all numbers in the interval [L,R]
		std::vector<int> palin(R-L+1,-1);
		
		for(int i=L; i<=R; i++){
			palin[i-L]=is_palindrome(i);
		}
		
		//count number of palindromic subintervals
		int counter = 0;
		//sample all subintervals of [L,R]...
		for(int i=L; i<=R; i++){
			for(int j=i; j<=R; j++){
				//subinterval is [i,j]
				counter+=is_palindromic_range(i-L,j-L,palin);
			}
		}
		
		//return number of interesting subintervals
		std::cout << counter << std::endl;
		
	}
	
	//clean up
	ifs.close();
	return 0;
}