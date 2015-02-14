#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <assert.h>

/*Challenge description:
https://www.codeeval.com/open_challenges/101/
*/


/* Format of input file is not checked */
/* This programs checks whether 4 points on the plane form a square, in any given orientation (sides of square need not be aligned with the axis) */


class Point2D{
private:
	double X;
	double Y;
public:
	Point2D(double x, double y):X(x),Y(y){};
	Point2D(const Point2D& A):X(A.get_X()),Y(A.get_Y()){};
	Point2D():X(0.0),Y(0.0){};
	~Point2D(){};
	double get_X() const {return X;};
	double get_Y() const {return Y;};
	void set_X(double x){this->X=x;};
	void set_Y(double y){this->Y=y;};
	Point2D& operator=(const Point2D&);
	double operator*(const Point2D&);
	double norm_sq();
	void print() const;
};

double Point2D::operator*(const Point2D& B){
	return this->X * B.get_X()+ this->Y * B.get_Y();
}
Point2D& Point2D::operator=(const Point2D& B){
	this->X=B.get_X();
	this->Y=B.get_Y();
	return *this;
}

double Point2D::norm_sq(){
	return X*X+Y*Y;	
}

Point2D operator-(const Point2D& A, const Point2D& B){
	double x = A.get_X()-B.get_X();
	double y = A.get_Y()-B.get_Y();
	return Point2D(x,y);
}

void Point2D::print() const{
	std::cout << X <<", "<<Y<<std::endl;
}


double cross_product(const Point2D& a, const Point2D& b){
	return a.get_X()*b.get_Y()-a.get_Y()*b.get_X();
}


/* Stores the 4 points in clockwise order */
class Quadrilateral{
private:
	Point2D * vertices;
	bool degenerated; //true is quadrilateral points are all on a straight line
public:
	Quadrilateral(Point2D *);
	~Quadrilateral(){delete[] vertices;};
	void order();
	void print();
	bool is_square();
};




/* Return 1 if all points are to right of vector ab, 0 otherwise and -1 if all points are on the same line */
int fun(const Point2D& a, const Point2D& b, const Point2D * points, int size){
	//a.print();
	//b.print();
	Point2D v = b-a;
	Point2D w;
	//std::cout << "fun STARTS reference points (v=b-a): "<<std::endl;
	//a.print();
	//b.print();
	bool in_line=true;
	for(int i=0; i<size; i++){
		//std::cout << "considering point i= "<<i<<std::endl;;
		//points[i].print();
		w = points[i]-a;
		//std::cout << "w=point i-a= ";
		//w.print();
		//std::cout << "vxw= "<<cross_product(v,w)<<std::endl;
		if(cross_product(v,w)>0){
			//std::cout<<", which is to the left, so fun EXITS"<<std::endl;
			return 0;
		}else if(cross_product(v,w)!=0){
			in_line=false;
		}
		//std::cout<<", which is to the right"<<std::endl;
	}
	
	if(in_line){
		return -1;
	}else{
		//std::cout << "so this point is the next one, and fun EXITS"<<std::endl;
		return 1;
	}
}

/* Reorders the vertices to be placed in clockwise order */
void Quadrilateral::order(){
	int ordering[4] = {-1,-1,-1,-1};
	//find leftmost vertex
	int lm=0;
	for(int i=1; i<4; i++){
		if(vertices[i].get_X() < vertices[lm].get_X()){
			lm = i;
		}
	}
	ordering[0]=lm;
		
	//start moving clockwise from lm vertex, until we come back to it
	int counter =1;
	int p=lm;//current vertex
	int pos;
	
	do{
		for(int i=0; i<4; i++){
			if( i!=p ){
				pos = fun(vertices[p],vertices[i],vertices,4);
				if( pos == 1 ){
					ordering[counter]=i;
					counter++;
					p=i;
					break;
				}else if(pos == -1){
					//then order does not matter much
					this->degenerated=true;
					return;
				}
			}
		}
		
	}while(p!=lm);
	
	
	//order vertices acording to ordering array
	Point2D * ordered = new Point2D[4];
	for(int i=0; i<4; i++){
		ordered[i] = vertices[ordering[i]];
	}
	for(int i=0; i<4;i++){
		vertices[i] = ordered[i];
	}
	
	this->degenerated=false;
	
	//clean up
	delete[] ordered;
	
}

Quadrilateral::Quadrilateral(Point2D * v){
	//copy arguments into array of 2D points
	vertices = new Point2D[4];
	
	for(int i=0; i<4; i++){
		vertices[i] = v[i];
	}
	//Order points in array (clockwise or anticlockwise)
	order();
}

void Quadrilateral::print(){
	for(int i=0; i<4; i++){
		vertices[i].print();
	}
	std::cout << std::endl;
}



/* A quadrilateral is a square if: */
/* 1) All its angles (or equivalently just 3 of them) are 90 degrees, ie vectors dot product is 0 */
/* 2) All its sides (or equivalently just 3 of them, if 1 holds) are equal */
bool Quadrilateral::is_square(){
	if(this->degenerated){
		return false;
	}
	bool isSquare = true;
	/* Build vectors */
	Point2D * vectors = new Point2D[4];
	for(int i=0; i<3; i++){
		vectors[i] = vertices[i+1]-vertices[i];
	}
	vectors[3] = vertices[0]-vertices[3];
	
	/* Check sides first */
	double side_sq = vectors[0].norm_sq();
	for(int i=1; i<4; i++){
		if( side_sq - vectors[i].norm_sq() > 1e-6 ){
			isSquare = false;
			break;
		}
	}
	// if we're here, all the sides are equal. Exclude the degenerate case:
	if(side_sq < 1e-6){
		isSquare=false;
	}
	
	/* Check angles */
	if(isSquare){
		for(int i=0;i<3;i++){
			if(vectors[i]*vectors[i+1]>1e-6){
				isSquare = false;
				break;
			}
		}
	}
	//if weve made it this far, the last angle is also 90 degrees: no need to check
	
	/* Clean up */
	delete[] vectors;
	
	/* Return answer */
	return isSquare;
}




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
	
	std::string line,word;
	std::stringstream ss;
	double x,y;
	Point2D point;
	int flag,i=0;
	
	Point2D * points = new Point2D[4];
	
	//Read whole file and store in memory			
	while( std::getline(ifs, line) ){
		ss.clear();
		ss.str(line);
		i=0;
		while( ss >> word ){
			flag = sscanf(word.c_str(),"(%lf,%lf), ",&x,&y);
			if(flag !=2){
				std::cout << "Error reading vertices from file. Aborting..." << std::endl;
				return 1;
			}
			points[i] = Point2D(x,y);
			i++;
			//reset word
			word="";
		}
		Quadrilateral my_quad = Quadrilateral(points);
		std::cout << std::boolalpha << my_quad.is_square() << std::endl ;
	}
	
		
	
	//clean up
	delete[] points;
	ifs.close();
	return 0;
}
