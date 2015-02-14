#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

/*Challenge description: 
https://www.codeeval.com/open_challenges/172/
*/

// Note: format of input file is not checked.

template<class T>
void print_vector(const std::vector<T>& v){
	typename std::vector<T>::const_iterator it;
	for(it=v.begin(); it != v.end(); it++){
		std::cout << *it << " ";
	}//there is a trailing space, not correcting because it is irrelevant.
	std::cout << std::endl;
}

//breaks num into its digits and returns the sum
int sum_digits(int num){
	int dsum = 0;//digit sum
	
	while(num!=0){
		dsum += num-10*(num/10); // extract last digit
		num=num/10; //new number with last digit removed
	}
	
	return dsum;
}

// checks whether the credit card number is valid, according to:
//http://en.wikipedia.org/wiki/Luhn_algorithm
bool is_valid(std::vector<int> ccn){
	std::vector<int>::reverse_iterator rit;
	//std::vector<int> v(ccn); // copy constructor
	for(rit=ccn.rbegin()+1; rit<ccn.rend(); rit+=2){
		*rit*=2;
	}
		
	int total_sum=0;
	for(rit=ccn.rbegin(); rit!=ccn.rend(); rit++){
		total_sum+=sum_digits(*rit);
	}
	if( total_sum % 10 == 0){
		return true;
	}else{
		return false;
	}
}



int main(int argc , char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	std::string line, word;
	std::stringstream ss;
	std::vector<int> ccn; //credit card number
	while(std::getline(ifs,line)){
		ss.clear();
		ss.str(line);
		ccn.clear();
		while(ss >> word){
			for(int j=0; j<(int)word.length(); j++){
				ccn.push_back(word[j]-'0');
			}
		}
		
		std::cout << is_valid(ccn) <<std::endl;
	}
	
	ifs.close();
	return 0;
}