#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>

/*Challenge description: 
https://www.codeeval.com/open_challenges/146/
*/

/* Warning: Format of the input file is not checked */


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




/*Main program */
int main(int argc , char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	
	std::string line;
	int l,d,n;
	int additional_bats;
	std::vector<int> v;
	
	while(std::getline(ifs,line)){
		/* Get input data */
		string_to_vector(line, v);
		l = v[0];
		d = v[1];
		n = v[2];
		assert(n+3 == v.size());
		
		/*Calculate bats*/
		additional_bats=0;
		
		for(int i=3; i<v.size()-1; i++){
			additional_bats += -1+(v[i+1]-v[i])/d;
		}
		if(n>0){
			//left side of the rope:
			if( v[3]>6 ){
				additional_bats += (v[3]-6)/d;
			}
			//right side of the rope
			if( v[v.size()-1] < l-6 ){
				additional_bats += (l-6-v[v.size()-1])/d;
			}
		}else{
			additional_bats = 1+(l -12)/d;
		}
		/* return number of additional bats */
		std::cout << additional_bats <<std::endl;
	}
	
	//clean up
	ifs.close();
	return 0;
}