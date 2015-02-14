#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

/*Challenge description:
https://www.codeeval.com/open_challenges/140/
*/

int main(int argc, char ** argv){
	/* Health check */
	if(argc !=2 ){
		std::cout<< "Call as ./data_recovery <path/to/file/filename>" << std::endl;
		return 1;
	}
	/* Open input file */
	std::ifstream myfile;
	myfile.open(argv[1]);
	
	if(!myfile.is_open()){
		std::cout << "Error opening the file.\nAborting..."<<std::endl;
		return 1;
	}
	
	std::string line;
	std::stringstream ss;
	
	std::vector<std::string> word_vec;
	std::vector<int> pos_vec;
	std::string word;
	int breaking_point;
	int pos;
	std::string mywords, mypos; 
	/* Read from file, line by line */
	while( std::getline(myfile, line) ){
		/* Separate words and numbers */
		breaking_point = line.find_last_of(';');
		mywords= line.substr(0,breaking_point);
		mypos = line.substr(breaking_point+1);
		
		/* Save words and numbers in ordered vectors */
		ss.clear();
		ss.str(mywords);
		word_vec.clear();
		do{
			ss >> word;
			word_vec.push_back(word);
		}while(ss.tellg()!=-1);
		ss.clear();
		ss.str(mypos);
		pos_vec.clear();
		do{
			ss >> pos;
			pos_vec.push_back(pos);
		}while(ss.tellg()!=-1);

		std::string last_word = word_vec[word_vec.size()-1];
		
		/* Reorder when printing to screen */
		std::vector<std::string> ordered_words(word_vec.size(),last_word);
		
		for(int i=0; i<pos_vec.size(); i++){
			ordered_words[pos_vec[i]-1] = word_vec[i];
		}
		
		/* Print solution */
		for(int i=0; i<ordered_words.size(); i++){
			if(i!=0){
				std::cout<< " ";
			};
			std::cout << ordered_words[i];
		}
		std::cout<< std::endl;
		
	}
	
	
	/* Cleaning...*/
	myfile.close();
	
	return 0;
}