#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>

/*Challenge description: 
https://www.codeeval.com/open_challenges/66/
*/

/* Prints a vector: it does not end with a newline*/
template <class T>
void print_vector(std::vector<T> v){
	typename std::vector<T>::iterator it=v.begin();
	std::cout << *it;
	for(it=v.begin()+1; it!=v.end(); it++){
		std::cout << " "<< *it;
	}
}


/* Given a row a in Pascal's triangle, returns and prints the next row b */
void next_row_pascal(const std::vector<long>& a, std::vector<long>& b){
	b.clear();
	b.push_back(1);
	if(a.size()==0){
		print_vector(b);
		return;//get out of function
	}else if(a.size()==1){
		b.push_back(1);
		print_vector(b);
		return;//all done, get out of here
	}
	//std::vector<int> b;
	std::vector<long>::const_iterator it;
	
	for(it=a.begin()+1; it!=a.end(); it++){
		b.push_back( *(it-1) + *it );
	}
	b.push_back(1);
	
	assert(b.size()==a.size()+1);
	print_vector(b);
}



/* Prints Pascal triangle up to depth n*/
void pascal(int n){
	std::vector<long> row;
	std::vector<long> next_row;
	for(int i=0; i<n; i++){
		next_row_pascal(row,next_row);
		if(i!=n){
			std::cout << " ";
		}
		row = next_row;
	}
	std::cout << std::endl;
}

/* Main program */
int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		std::cout << "Error opening file. Aborting..."<< std::endl;
		return 1;
	}
	
	std::string line;
	int depth;
	
	while(ifs >> depth ){//std::get_line(ifs,line) ){
		pascal(depth);
	}
	
	ifs.close();
	return 0;
}