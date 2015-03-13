#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

/*Challenge description:
https://www.codeeval.com/open_challenges/18/
*/

int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	std::string line;
	std::stringstream ss;
	double angle, dec; // angle and decimal part
	int deg,min,sec;   // degrees, minutes and seconds
	
	while(std::getline(ifs, line)){
		ss.clear();
		ss.str(line);
		ss >> angle;
		deg = floor(angle);
		dec = angle-deg;
		min = floor(60*dec);
		dec = 60*dec-min;
		sec = floor(60*dec);
		std::cout << deg <<"."<< std::setfill('0') << std::setw(2)<< min<<"'"<<std::setw(2)<<sec<<"\""<<std::endl;

	}
	
	
	ifs.close();
	return 0;

}