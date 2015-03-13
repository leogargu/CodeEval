#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <vector>

/* Challenge description:
https://www.codeeval.com/open_challenges/85/
*/

//print an array to screen: useful for debugging
void print(int * a, int L){
	for(int i=0; i<L; i++){
		std::cout << a[i]<<" ";
	}
	std::cout << std::endl;
}

//print vector to screen: useful for debugging
template<class T>
void print(std::vector<T> v){
	typename std::vector<T>::iterator it;
	for(it=v.begin(); it!=v.end();it++){
		std::cout << *it <<" ";
	}
	std::cout << std::endl;
}

//auxiliary sorting function to use with algorithm std::sort
bool sort_func (int i,int j) { return (i<j); }



//for each i st k<=i<n, m[i]=min integer NOT in set {m[i-k] to m[i-1]}
int find_next(std::vector<int> v, int k, std::vector<int>::iterator it){
	//create previous k values vector
	std::vector<int> m(it-k,it);
	//sort previous values vector
	std::sort(m.begin(),m.end(),sort_func);
	//find min non-negative integer NOT contained in m
	for(int i=0; i<k; i++){
		if(m[i]>i){//m is sorted
			return i;
		}
	}
	return k;
	
}


int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		std::cout << "error opening input file. Aborting..." << std::endl;
		return 1;
	}
	
	std::string line,num;
	std::stringstream ss;
	int inputs[6]; // in increasing order, this stores: n,k,a,b,c,r;
	int counter;
	
	
	while(std::getline(ifs,line)){
		ss.clear();
		ss.str(line);
		counter=0;
		while(ss.good()){
			std::getline(ss, num, ',');
			inputs[counter] = atoi( num.c_str());
			counter++;
		}
		assert(counter==6);
		
		
		//Populate array m with known values (0 to k-th)
		std::vector<int> m(inputs[0],0);
		m[0]=inputs[2];
		for(int i=1; i<inputs[1] ; i++){
			m[i]=(inputs[3] * m[i - 1] + inputs[4]) % inputs[5];
		
		}
		
		
		std::vector<int>::iterator it=m.begin();
		
		for(it=m.begin()+inputs[1]; it!=m.end(); it++){
			*it=find_next(m,inputs[1],it);
		}
		
		
		
		//return solution
		std::cout << m[inputs[0]-1]<< std::endl;
		
				
	}
	
	
	//clean up
	ifs.close();
	return 0;
}
