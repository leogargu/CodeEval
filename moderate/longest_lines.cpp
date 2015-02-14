#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm> //std::sort

/*Challenge description:
https://www.codeeval.com/open_challenges/2/
*/

/* Assuming input file is correctly formatted and the program is called correctly */
/* If input data contains special characters/accents this is not guaranteed to work */
/* Lines of equal length do not receive special treatment */


/* ordering function */
bool reverse_order(int i, int j){
	return i>j;
}


/* Sorts array of integers */
template <class T>
void sort(std::vector<T>& n){
	std::sort(n.begin(), n.end(), reverse_order); 
}


/* Finds first position of element e in vector v*/
/* Returns -1 if element is not in the vector */
template <class T>
int pos(T e, std::vector<T> v){
	for(int i=0; i<v.size(); i++){
		if(e==v[i]){
			return i;
		}
	}
	return -1;
}


/* Main program */
int main(int argc, char ** argv){
	std::ifstream fs; 
	fs.open(argv[1]);
	if( !fs.is_open() ){
		return 1;
	}
	
	std::string line;
	
	//get first line (number of lines to output)
	std::getline(fs,line);
	int num = atoi(line.c_str()); 
	
	std::vector<int> n_chars;
	std::vector<std::string> v_lines;
	
	//read rest of lines, and store them
	while( std::getline(fs,line) ){
		n_chars.push_back( line.size() );	
		v_lines.push_back( line );
		
	}
	
	std::vector<int> n_chars_sorted(n_chars); // copy n_chars
	sort(n_chars_sorted);
	
	for(int i=0; i<num; i++){
		std::cout << v_lines[ pos(n_chars_sorted[i], n_chars) ] << std::endl;
	}
	
	//clean up
	fs.close();
	
	return 0;
}