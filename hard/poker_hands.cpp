#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

/*Challenge description:
https://www.codeeval.com/open_challenges/86/
*/

/*-----------------------*/
/*     	Class CARD  	 */
/*    Value and suit	 */
/*-----------------------*/
class Card{
friend class Hand;
public:
	//constructors
	Card(): suit('N'),value('0'),v(0){};
	Card(std::string);
	//destructor
	~Card(){};
	//methods
	int value2int(char);
	void print();
private:
	char suit; 
	char value;// 1,2,3...,9,T,J,Q,K,A
	int v; // Ten=10, Jack = 11, Queen=12, King=13, Ace=14
	
};

//Convert value char to int value
int Card::value2int(char c){
	int val;
	switch(c){
		case 'T':
			val = 10;
			break;
		case 'J':
			val = 11;
			break;
		case 'Q':
			val = 12;
			break;
		case 'K':
			val = 13;
			break;
		case 'A':
			val = 14;
			break;
		default:
			val = c-'0';
	}
	return val;
}

//constructor
Card::Card(std::string s){
	value = s[0];
	suit = s[1];
	v = value2int(value);
}


void Card::print(){
	std::cout << "Value: "<<v<<" Suit:" << suit<<std::endl;
}


/*-----------------------*/
/*     	Class HAND  	 */
/* Collection of 5 cards */
/*-----------------------*/
class Hand{
public:
	//constructors
	Hand(Card[]);
	Hand(){};
	//destructor
	~Hand(){};
	//methods
	void order();
	void add(Card);
	void print();
	void rank(int *);
	bool same_suit();
	bool consecutive();
	void clear();
	int pos_value(int);
private:
	std::vector<Card> cards;
	
};

//remove all cards in hand
void Hand::clear(){
	cards.clear();
}

//add card to hand
void Hand::add(Card c){
	cards.push_back(c);
}

//constructor
Hand::Hand(Card c[]){
	for(int i=0; i<5; i++){
		cards.push_back(c[i]);
	}
}

void Hand::print(){
	for(unsigned int i=0; i<cards.size(); i++){
		cards[i].print();
	}
}

//checks if all cards in hand are of the same suit
bool Hand::same_suit(){
	char s = cards[0].suit;
	for(unsigned int i=1;i<cards.size();i++){
		if(s!=cards[i].suit){
			return false;
		}
	}
	return true;
}

//cheks if all cards in hand are consecutive
//Note: The Ace behaves in a special way:
//https://www.pokerstars.uk/poker/games/rules/hand-rankings/
//deactivated here because CodeEval challenge description does not call for it
#define ACE_LH	0
bool Hand::consecutive(){
	unsigned int hand_length= cards.size();
	int prev = cards[0].v;
	
	if(prev==14 && ACE_LH){//if the ace is the top card...
		if(cards[1].v==5){
			prev=6;
		}
	}
	
	for(unsigned int i=1;i<hand_length;i++){ 
		if(cards[i].v!=prev-1){
			return false;
		}
		prev=cards[i].v;
	}
	
	return true;
}

/*Returns a 2 element int array (argument) with:
r[0] - the type of the rank, from 1-9 or -1 (see list below)
r[1] - the value of the (highest) rank, when applicable, -1 otherwise
r[2] - the value of the second highest rank, when present, -1 otherwise

example: pair of queens -> r=[9,12]
	four aces -> r=[3,14]
	straight -> r[6,-1]

Note that CodeEval description does not compare suits in case of a draw 
(if doing so, it would be: 1-spades, 2-hearts, 3-diamonds, 4-clubs)

Ranks:	
9 if Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
8 if Straight Flush: All cards are consecutive values of same suit.
7 if Four of a Kind: Four cards of the same value.
6 if Full House: Three of a kind and a pair.
5 if Flush: All cards of the same suit.
4 if Straight: All cards are consecutive values.
3 if Three of a Kind: Three cards of the same value.
2 if Two Pairs: Two different pairs.
1 if One Pair: Two cards of the same value.
-1 otherwise ----High Card: Highest value card.
*/
void Hand::rank(int * r){
	//order the hand first
	this->order();
	
	//check some status
	bool onesuit = this->same_suit();
	bool consec = this->consecutive();
		
	//default:
	r[0] = -1;
	r[1] = -1;
	r[2] = -1;
	
	//check hands in more or less descending order
	if( onesuit ){ //at the very least it is a flush
		if(consec){//could be straight flush or royal flush
			if(cards[5].v==14){
				//royal flush
				r[0]=9;
				//r[1]=-1;//we could encode suit here
				return;
			}else{ //straight flush
				r[0]=8;
				//r[1]=-1;//could encode suit here
				return;
			}
		}
		//this hand can be flush, if it is not a four of a kind or full house: store provisionally but do not return
		r[0]=5;
		//r[1]=-1;//could encode suit here
	}else if(consec){
		//hand is Straight at the very least
		r[0]=4;
	}
	
	//now check for repeated values:first scan...
	int prev = cards[0].v;
	int rep=1,counter=0;
	//Will store info as: house=[[num repetitions,value],[num repetitions,value]]
	int house[2][2];
	//initialise:
	house[0][0]=-1;
	house[0][1]=-1;
	house[1][0]=-1;
	house[1][1]=-1;
	
	for(unsigned int i=1; i<cards.size(); i++){
		if(cards[i].v==prev){
			rep++;
		}else if(rep>1){
			house[counter][0]=rep;
			house[counter][1]=prev;
			counter++;
			rep=1;
		}
		prev=cards[i].v;
	}
	//Note that last card is not accounted for, fixing it here
	if(rep>1){
		house[counter][0]=rep;
		house[counter][1]=prev;
	}
	
		
	//...then analyze.
	if(house[0][0]==4){//four of a kind
		r[0]=7;
		r[1]=house[0][1];
	}else if(house[0][0]==3){//three of a kind or full house
		if(house[1][0]==2){//full house
			r[0]=6;
			r[1]=house[0][1];
			r[2]=house[0][2];
		}else{//three of a kind
			r[0]=3;
			r[1]=house[0][1];
		}
	}else if(house[0][0]==2){//one pair,two pairs or full house
		if(house[1][0]==3){//full house
			r[0]=6;
			r[1]=house[1][1];
			r[2]=house[0][1];
		}else if(house[1][0]==2){//two pairs
			r[0]=2;
			//cards are ordered in decreasing order: house[0][1] > house[0][2]
			r[1]=house[0][1];
			r[2]=house[0][2];
		}else{//one pair
			r[0]=1;
			r[1]=house[0][1];
		}
	}
	
}



//orders cards in hand in decreasing order
//uses bubble sort
void Hand::order(){
	Card tempcard;
	bool swapped = true;
	while(swapped){
		swapped=false;
		for(int i=0; i<4; i++){
			if(cards[i].v < cards[i+1].v){
				tempcard=cards[i];
				cards[i]=cards[i+1];
				cards[i+1]=tempcard;
				swapped=true;
			}
		}
	}
}

//returns the value of teh card in position i in the hand
int Hand::pos_value(int i){
	return cards[i].v;
}



/*---------------*/
/* Main Program  */
/*---------------*/
int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	std::string line,card_str;
	std::stringstream ss;
	Hand left, right;
	int l[3],r[3];
	
	while(std::getline(ifs,line)){
		ss.clear();
		ss.str(line);
		right.clear();
		left.clear();
		
		//get left hand
		for(int i=0; i<5; i++){
			ss>>card_str;
			Card mycard(card_str);
			left.add(mycard);
		}
		
		//get right hand
		for(int i=0; i<5; i++){
			ss>>card_str;
			Card mycard(card_str);
			right.add(mycard);
		}
		

		//determine rank of hands: this orders the hands too
		left.rank(l);
		right.rank(r);
		
		//compare ranks of hands
		std::string winner="none";		
		
		if(l[0]>r[0]){
			winner="left";
		}else if(r[0]>l[0]){
			winner="right";
		}else{//boths hands have same rank
			if(r[1]>l[1]){
				winner="right";
			}else if(l[1]>r[1]){
				winner="left";
			}else if(r[2]>l[2]){
				winner = "right";
			}else if (l[2]>r[2]){
				winner="left";
			}else{//winner is decided comparing side cards, from highest value to lowest. Cards in hands are ordered since rank() was called
				for(int i=0; i<5; i++){
					if(left.pos_value(i)>right.pos_value(i)){
						winner="left";
						break;
					}else if(right.pos_value(i)>left.pos_value(i)){
						winner="right";
						break;
					}//else, continue comparing next card
				}
			}
		}
		
		//output the winner
		std::cout << winner << std::endl;		

	}
	
	//clean up
	ifs.close();
	
	return 0;
}


