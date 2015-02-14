#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/*Challenge description:
https://www.codeeval.com/open_challenges/153/
*/

/* locked = false, unlocked=true*/


// first pass: LOCK every second door
void beat_lock(bool d[], int size){ //arrays are passed by reference by default
	for(int i=1; i<size; i+=2){
		d[i] = false;
	}
	
}

//second pass: FLIP every third door
void beat_flip(bool d[],int size){
	for(int i=2; i<size; i+=3){
		d[i] = !d[i];
	}
}

int main(int argc, char** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	
	std::string line;
	std::stringstream ss;
	
	int num_doors,iter;
	int unlocked;
	bool * doors;
	
	while(std::getline(ifs,line)){
		ss.clear();
		ss.str(line);
				
		ss >> num_doors >> iter;
		
		doors = new bool[num_doors];
		
		//initially all doors are unlocked
		for(int i=0; i<num_doors; i++){
			doors[i]=true;
		}
		
		//special cases
		if(iter == 0 || num_doors ==0){
			std::cout << num_doors <<std::endl;
			continue;
		}
		
		
		//if we are here, iter >=1, so the last door will be flipped
		
		for(int i=0; i<iter-1; i++){
			beat_lock(doors,num_doors);
			beat_flip(doors,num_doors);
		}
		
		
		//last pass
		doors[num_doors-1] = !doors[num_doors-1];
		
		//return result
		unlocked=0;
		for(int i=0; i<num_doors; i++){
			if(doors[i]){
				unlocked++;
			}
		}
		
		std::cout << unlocked << std::endl;
	}
	
	ifs.close();
	return 0;
}