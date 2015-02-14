#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> //pow
#include <algorithm> //reverse

/*Challenge description: 
https://www.codeeval.com/open_challenges/44/
*/

// Not necessary to reverse vectors, but done here to remain sane.

/* reverses order of elements in a vector*/
/* Not used, implemented just for practice */
template <class T>
void reverse_vector(std::vector<T>& v){
	typename std::vector<T>::iterator it;
	typename std::vector<T>::iterator itb=v.end()-1;
	const long size = v.size();
	T aux;
	for(it=v.begin(); it!=(v.begin()+(size/2)); it++){
		aux = *it;
		*it = *itb;
		*itb = aux;
		itb--;
	}
}

/* stores digits in num into vector v */
//this function removes leading zeroes
void num_to_digits(long num, std::vector<int>& v){
	v.clear();
	int digit;
	while( num ){
		digit = num - 10*(num/10);
		v.push_back(digit);
		num = num/10;
	}
	std::reverse(v.begin(),v.end());	
	//reverse_vector(rv); //<---Alternative option, using function above
}

/* Function equivalent to num_to_digits, but this version keeps the leading zeroes */
int string_to_digits(const std::string& line, std::vector<int>& v){
	v.clear();
	int num_digits = 0;
	std::string::const_iterator it;
	for(it=line.begin(); it!=line.end(); ++it){
		v.push_back(*it-'0'); // ASCII
		num_digits++;
	}
	return num_digits;
}



/* Takes digits vector (right order) and parses it to an integer */
//note this function eliminates leading zeroes: to keep them, use funcion pint_digits
long digits_to_num(const std::vector<int>& v){
	std::vector<int>::const_reverse_iterator rit;
	int i=0;
	long num=0;
	for(rit=v.rbegin(); rit!=v.rend(); rit++){
		num += (*rit) * (long)pow(10,i);
		i++;
	}
	return num;
	
}

/* Prints digits consecutively to stdout, to form an integer */
void print_digits(std::vector<int> digits){
	std::vector<int>::iterator it;
	for(it=digits.begin(); it!=digits.end(); it++ ){
		std::cout << *it;
	}
	std::cout << std::endl;
}

/*prints vector as it is */
template <class T>
void print_vector(std::vector<T> v){
	typename std::vector<T>::iterator it = v.begin();
	std::cout << *it;
	for(it=v.begin()+1; it!=v.end(); it++){
		std::cout << " " << *it ;
	}
	std::cout << std::endl;
}


/* insertion sort */
/* returns true if some sorting has occurred, false if input vector was already sorted*/
template <class T>
bool insertion_sort(std::vector<T>& v){
	int i,j;
	T aux;
	const int size = v.size();
	bool flag = false;
	for(i=1; i<size; i++){
		for(j=i; j>0 ;j--){
			if( v[j-1]>v[j] ){
				aux=v[j];
				v[j]=v[j-1];
				v[j-1]=aux;
				flag = true;
			}	
		}
	}
	return flag;
}




/* getting new head for subvector (from right hand side: head is left-most element)*/
/* Returns index of suitable head, -1 if no suitable head has been found*/
int get_new_head(std::vector<int> w){
	int old_head = w[0];
	int new_head_idx = -1;
	int new_head = 10;
	for(int i=1; i<w.size(); i++){
		if( w[i] > old_head && w[i]<new_head ){
			new_head = w[i];
			new_head_idx = i;
		}
	}
	return new_head_idx;
}




//v is the original digits vector
long fun(int n, const std::vector<int>& v){
	std::vector<int>::const_iterator it = v.end();
	std::vector<int> w,u,sol;
	int head_idx;
	const int size = v.size();
	int i=0;
	
	if (n>size){	//we need an extra zero
		u.assign(v.begin(),v.end());
		insertion_sort(u);
		//careful here with zeroes already present
		i=0;
		while( u[i] == 0 ){
			i++;
		}

		sol.push_back(u[i]); //smallest non-zero digit
		//then, all zeroes plus the extra zero
		for(int j=0; j<i+1; j++){
			sol.push_back(0);	
		}
		//now the rest of the sorted digits
		sol.insert(sol.end(), u.begin()+i+1, u.end());
		print_digits(sol);
		return digits_to_num(sol);
		
	}
	
	if( n==2 ){
		w.assign(it-2,it);
		if (w[0]<w[1]){
			sol.assign(v.begin(),it-2);
			sol.push_back(w[1]);
			sol.push_back(w[0]);
			print_digits(sol);
			return digits_to_num(sol);
		}else{
			return fun(n+1,v);
		}
	}
	
	if(n>2){
		w.assign(it-n,it);
		head_idx = get_new_head(w);
		if( head_idx == -1){ //no new head was found: take n+1 digits
			return fun(n+1,v);
		}else{
			sol.assign(v.begin(),it-n);
			sol.push_back(w[head_idx]); //exclude head from remaining array
			u.assign(w.begin(),w.end()); //copy first..
			u.erase(u.begin()+head_idx);//...now delete head
			insertion_sort(u); //some rearrangement is already happening
			sol.insert(sol.end(), u.begin(), u.end());	
			print_digits(sol);
			return digits_to_num(sol);
		}
	}
	return -1;//avoid compilation warning
}
	
		

/* Main program */
int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if( !ifs.is_open() ){
		return 1;
	}
	
	std::string line;
	std::vector<int> v;
	int numint;
	
	while( std::getline(ifs,line) ){
		//convert line to digits
		numint = string_to_digits(line, v);
		//calculate next integer
		if(numint<2){
			std::cout << line << "0" << std::endl;
		}else{
			fun(2,v);
			//std::cout << fun(2, v) << std::endl;
		}
	}
	
		
	
	ifs.close();
	return 0;
}