#include <iostream>
#include <vector>
#include <cmath>
/*Challenge description:
https://www.codeeval.com/open_challenges/4/
*/


bool is_prime(int n, const std::vector<int>& primes){
	std::vector<int>::const_iterator it;
	for(it=primes.begin(); it!=primes.end(); it++){//actually only need to check up to ceil(sqrt(n))
		if(n%(*it)==0){
			return false;
		}
		/*if(*it>ceil(sqrt(n))){
			return true;
		}*/
	}
	return true;
}


int main(int argc, char ** argv){
	
	long sum = 2; 
	std::vector<int> primes;
	
	primes.push_back(2);
	
	int i=3;
	int counter = 1;
	while( counter < 1000){
		if(is_prime(i,primes)){
			sum+=i;
			primes.push_back(i);
			counter++;
		}//else do nothing
		i++;
	}
	
	std::cout << sum << std::endl;

	return 0;
}
