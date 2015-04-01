#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

/*Challenge description
https://www.codeeval.com/open_challenges/65/
*/

//global constants (board is hard-coded in main())
const int r=3;
const int c=4;
//hard-coded board
const char board[r][c]={{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
	



/*Auxiliary class Coordinates (Coords) */
class Coords{
public:
	//constructor
	Coords(int a, int b):x(a),y(b){};
	//destructor
	~Coords(){};
	//friend functions:
	friend std::ostream& operator<<(std::ostream &, const Coords &);
	friend void advance(const Coords, char , std::vector<Coords> &);
	//methods
	void print();
	int get_x() const {return x;};
	int get_y() const {return y;};
private:
	int x,y;
};

bool operator==(const Coords& lhs, const Coords& rhs) {
	return ((lhs.get_x() == rhs.get_x()) && (lhs.get_y() == rhs.get_y()));
}


std::ostream& operator<<(std::ostream & os, const Coords & obj)
{
  std::cout << "("<<obj.x<<","<<obj.y<<")";
  return os;
}

void Coords::print(){
	std::cout <<"("<< x<< ","<<y<<")"<<std::endl;
}


/* Auxiliary class Node */
template<class T>
class Node{
public:
	//constructor
	Node(T c):value(c),parent(NULL){children.clear();};//assert children.size()==0 instead?
	//copy constructor
	Node(const Node & n):value(n.value),children(n.children),parent(n.parent){};
	//destructor
	~Node(){parent=NULL;remove_children();children.clear();};
	//methods
	void add_child(T);
	void print() const;
	Node * get_parent(){return parent;};
	void print_children() const;
	std::vector<Node*> & get_children(){return children;};
	void set_value(T v){value=v;};
	T get_value(){return value;};
	void remove_children();
private:
	T value;
	std::vector< Node *> children;
	Node * parent;
};


/*Member methods */
template<class T>
void Node<T>::remove_children(){
	for(int i=0; i<children.size(); i++){
		delete children[i];
	}
}


template<class T>
void Node<T>::print_children() const{
	for(int i=0; i<children.size(); i++){
		std::cout <<children[i]->value <<" ";
	}
	std::cout << std::endl;
}

template<class T>
void Node<T>::print() const{
	std::cout << value ;
}


template<class T>
void Node<T>::add_child(T v){
	children.push_back(new Node<T>(v));
	children[children.size()-1]->parent=this;
}


//returns true if e is contained in v
template<class T>
bool is_element(T e, std::vector<T> v){
	typename std::vector<T>::iterator it;
	for(it=v.begin(); it!=v.end(); it++){
		if(*it==e){
			return true;
		}
	}
	return false;
}

/* Non-member methods */
//Returns 0 if no repeated coords are found transversing the tree upwards from node n, 1 otherwise.
//Optional parameter wordlength used in logical assertion when this method is used to explore trees created from the board.
template<class T>
int transverse_up_reps(Node<T> * n, int wordlength=0){
	std::vector<Coords> walk;
	walk.clear();
	Coords step(0,0);
	Node<T> * p = n;
	while(p!=NULL){
		step = p->get_value();
		if(is_element(step,walk)){
			return 1; //repetiton happened to form the word
		}
		walk.push_back(step);
		p = p->get_parent();
	}
	if(wordlength){//root node adds one
		assert(walk.size()==wordlength+1);
	}
	return 0; //no repetitions, word found
}

//prints part of the tree accesible downwards from the given node n, all the tree if n is the root node
template<class T>
void print_down_tree(Node<T> & n, int level=0){
	std::cout <<"---level "<<level<<"---"<<std::endl;
	n.print();
	std::vector<Node<T> * > ch = n.get_children();
	if(ch.size()==0){
		std::cout <<"(leaf)"<<std::endl;
	}
	std::cout <<std::endl;
	for(int i=0; i<ch.size(); i++){
		print_down_tree(*ch[i], level+1);
	}
	
}


/* Algorithm methods */
void advance(const Coords current, char letter, std::vector<Coords> & next){
	next.clear();
	//check left:
	if( current.x>0 && board[current.x-1][current.y]==letter){
		next.push_back(Coords(current.x-1,current.y));
	}
	//check above:
	if( current.y>0 && board[current.x][current.y-1]==letter){
		next.push_back(Coords(current.x,current.y-1));
	}
	//check right:
	if( current.x<r-1 && board[current.x+1][current.y]==letter){
		next.push_back(Coords(current.x+1,current.y));
	}
	//check below:
	if( current.y<c-1 && board[current.x][current.y+1]==letter){
		next.push_back(Coords(current.x,current.y+1));
	}	
	
}


//finds list of all coords of letter on the board. 
void find_letter(const char letter, std::vector<Coords> & coords){
	coords.clear();
	for(int i=0; i<r; i++){
		for(int j=0;j<c; j++){
			if(letter==board[i][j]){
				coords.push_back(Coords(i,j));
			}
		}
	}
}


/* Auxiliary printing functions */
template<class T>
void print(std::vector<T> v){
	typename std::vector<T>::iterator it;
	for(it=v.begin();it!=v.end();it++){
		std::cout << *it<<" ";
	}
	std::cout << std::endl;
}

void print_board(){
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			std::cout << board[i][j]<<" ";
		}
		std::cout << std::endl;
	}	

}

template<class T>
void print_level(std::vector<Node<T> *> v){
	for(int i=0; i<v.size(); i++){
		v[i]->print();
	}
	std::cout <<std::endl;
}




/* main program */
int main(int argc, char ** argv){
	
	//std::cout << "Board under study: "<<std::endl;
	//print_board();
	
	//get input data
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	std::string line;
	
	std::vector<Coords> leaves_c;
	std::vector< Node<Coords> *> current_level, next_level, aux_level;
	
	bool flag;
	
	int pos=0;
	
	while(std::getline(ifs,line)){
		pos=0;
		//create root node just as reference: value is irrelevant
		Node<Coords> root(Coords(-1,-1));
		//scan whole board to find first letter in word
		find_letter(line[pos], leaves_c);
		//add leaves to root:
		for(int i=0; i<leaves_c.size(); i++){
			root.add_child(leaves_c[i]);
		}
		
		//get current level of nodes
		current_level.clear();
		current_level=root.get_children();
	
		//advance position along word
		pos=1;
		//until the end of the word...
		while(pos<line.length()){
			//...clear next level...
			next_level.clear();
			//...for each node in current level...
			for(int i=0; i<current_level.size(); i++){
				//...find possible next coords & save in leaves_c...
				advance(current_level[i]->get_value(), line[pos], leaves_c);
								
				//...create nodes for those coords & add to parent node...
				for(int j=0; j<leaves_c.size(); j++){
					current_level[i]->add_child(leaves_c[j]);
				}
				
				//Next level will be a concatenation of all the children nodes of each node in current level. Get subset of children & add to next level.
				aux_level=current_level[i]->get_children();
				for(int j=0;j<aux_level.size(); j++){
					next_level.push_back(aux_level[j]);
				}
			}
			
			//update->next level becomes current level
			current_level=next_level;
			//advance position along the word
			pos++;
			
		}
		
		
		//walk from last level up to check for duplicates
		if(current_level.size()==0){//word cannot be found
			std::cout <<  "False" <<std::endl;
		}else{//word was found but potentially by stepping on same position more than once
			flag=false;
			for(int i=0; i<current_level.size(); i++){
				if( transverse_up_reps(current_level[i],line.length())==0){
					flag=true;
					break;//exit for loop
				}//else do nothing: this particular path didn't yield a word, but others may.		
			}
			if(flag){
				std::cout << "True" << std::endl;
			}else{
				std::cout << "False"<< std::endl;
			}
		}
		
	}
		
	
	//clean up
	ifs.close();
	return 0;
}




