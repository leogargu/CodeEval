#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

/*Challenge description: 
https://www.codeeval.com/open_challenges/158/
*/


/* Format of input file is not checked */

/* Convert string containing numerical elements to vector */
template <class T>
void string_to_vector(const std::string& s, std::vector<T>& v){
	std::stringstream ss;
	ss.str(s);
	T n;
	v.clear();
	
	while( ss >> n ){
		v.push_back(n);
	}
}



/* Print a vector, no trailign spaces*/
template <class T>
void print_vector(std::vector<T> v){
	const int size = v.size();
	if(size){
		std::cout << v[0];
	}
	
	for(int i=1; i<size; i++){
		std::cout << " " << v[i];
	}
	std::cout << std::endl;
}


/* Performs n iterations of bubble sorts on a vector */
template <class T>
void bubble_sort_n(std::vector<T>& v, int num){
	const int size = v.size();
	T temp;
	bool sorted = true;
	
	for(int j=0; j<num; j++){
		sorted = true;
		for(int i=0; i<size-1; i++ ){
			if(v[i+1]<v[i]){
				temp = v[i];
				v[i] = v[i+1];
				v[i+1] = temp;
				sorted = false;
			}
		}
		if(sorted){
			break; //return.
		}
	}
}

int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if( !ifs.is_open() ){
		return 1;
	}
	
	std::string line;
	std::string sequence;
	std::vector<int> v;
	int num,idx;
	
	
	while( std::getline(ifs, line) ){
		//separate iterations from numbers to sort
		idx = line.find("|");
		sequence = line.substr(0, idx);
		num = std::stoi(line.substr(idx+2, 1));
		
		string_to_vector(sequence, v);
		bubble_sort_n(v,num);
		print_vector(v);
		
	}
	
	ifs.close();
	return 0;
}
