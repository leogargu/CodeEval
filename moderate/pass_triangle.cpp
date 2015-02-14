#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <assert.h>
#include <algorithm> //max


/*Challenge description: 
https://www.codeeval.com/open_challenges/89/
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




int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if( !ifs.is_open() ){
		return 1;
	}
	
	std::string line;
	int height=0;//number of lines in triangle 
	//vector containing lines in the file (converted into vectors of long ints)
	std::vector< std::vector<long> > triangle; 
	std::vector<long> v;	
	
	//Read whole file and store in memory			
	while( std::getline(ifs, line) ){
		height++;	
		string_to_vector(line, v);
		//health check: assert this is a triangle
		assert(v.size()==height); 
		//storing lines in reverse order
		triangle.push_back(v);	
	}
	
	v.clear();
	std::vector<long> w;
	
	std::vector < std::vector<long> >::reverse_iterator rit;
	std::vector<long>::iterator it;
	v = *triangle.rbegin(); //get last row
	int i=0;
	//Step along the triangle from base to top
	for(rit=triangle.rbegin()+1 ; rit!=triangle.rend(); rit++){
		w = *rit;
		
		for(it = w.begin(); it != w.end(); it++){
			i = it - w.begin();
			v[i] = std::max( *it + v[i], *it + v[i+1] );
		}
		
	}
	
	//return value
	std::cout << v[0] << std::endl;	
	
	//clean up
	ifs.close();
	return 0;
}
