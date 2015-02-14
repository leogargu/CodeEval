#include <iostream> /* std::cout, std::endl */
#include <fstream> /* file io */
#include <string> /* std::string */
#include <sstream>

/* Challenge information: 
https://www.codeeval.com/open_challenges/1/
*/

void fizz_buzz(int X, int Y, int N){
	char f='F';
	char b='B';
	bool flag;
	
	for(int i=1; i<=N; i++){
		if(i!=1){
			std::cout << " ";
		}
		
		flag = true;
		if( i%X==0 ){
			std::cout << f;
			flag = false;
		}
		if( i%Y == 0){
			std::cout << b;
			flag = false;
		}
		if( flag ){
			std::cout << i;
		}
	}
	
	std::cout << std::endl;
	
}

bool apply_constraints(int X, int Y, int N, int num_test_cases){
	return( X>=1 && X<=20 && Y>=1 && Y<=20 && N>=21 && N<=100 && num_test_cases<=20 );
}

int main (int argc, char * argv[]) {
	/* Parse arguments*/
	if(argc !=2 ){
		std::cout<< "Call as ./fizz_buzz <input file name>\nAborting..."<<std::endl;
		return 1;
	}

	/* Read from file */	
	std::ifstream myfile;
	myfile.open(argv[1],std::ios::in);

	std::string line;
	int X,Y,N;
	int flag;
	int num_test_cases=0;
	
	std::stringstream ss;
	if(myfile.is_open()){
		while ( std::getline (myfile,line) ){
			num_test_cases++;
			X=-1;
			Y=-1;
			N=-1;
			ss.clear();
			ss.str(line);
			
			ss >> X >> Y >> N;
			flag = ss.tellg();
									
			if ( N==-1 || flag!=-1 || Y==-1 || X==-1){//redundant: if N==-1 then Y and/or X  may be -1 too
				/* This line of the file is not valid*/
				continue;
			}
			/* Proper values of X, Y, N have been recovered*/
			if(apply_constraints(X,Y,N,num_test_cases)){
				fizz_buzz(X,Y,N);
			}
		}
  	}else{
  		std::cout << "could not open file " << argv[1] << std::endl;
  	}
  
  	/* Close input file */
  	myfile.close();
  	return 0;
}
