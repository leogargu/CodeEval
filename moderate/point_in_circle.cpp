#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

/* Challenge description:
https://www.codeeval.com/open_challenges/98/
*/

/* Format of input file is not checked */


/* 2D Point class */
class Point2D{
private:
	double X;
	double Y;
public:
	Point2D(){X=0.0;Y=0.0;};
	Point2D(double x, double y):X(x),Y(y){};
	Point2D(double p[]):X(p[0]),Y(p[1]){};
	~Point2D(){};
	double get_X() const {return X;};
	double get_Y() const {return Y;};
	void set_X(double x){X=x;};
	void set_Y(double y){Y=y;};
	Point2D& operator=(const Point2D&);
	double norm_sq();
};

double Point2D::norm_sq(){
	return X*X+Y*Y;
}

Point2D& Point2D::operator= (const Point2D & b){
	X = b.X;
	Y = b.Y;
	return *this;
}

Point2D operator- (const Point2D & a, const Point2D & b){
	return Point2D(a.get_X()-b.get_X(),a.get_Y()-b.get_Y());
}


/* Circle class */
class Circle{
private: 
	Point2D C;
	double R;
	
public:
	/* default constructor */
	Circle();
	/* a more useful constructor */
	Circle(Point2D center,double radius):C(center),R(radius){};
	/* destructor*/
	~Circle(){};
	/* getter methods */
	double get_radius() const;
	Point2D get_center() const;
	/*setter methods */
	void set_radius(double radius);
	void set_center(const Point2D& center);	
};

Circle::Circle(){
	R=0.0;
	C=Point2D();
}

double Circle::get_radius() const{
	return this->R;
}

Point2D Circle::get_center() const{
	return this->C;
}

void Circle::set_radius(double radius){
	this->R=radius;
}

void Circle::set_center(const Point2D& center){
	this->C = center;
}




/* Check whether a Point2D is in a Circle */
bool point_in_circle(const Point2D& point, const Circle& circle){
	Point2D diff = circle.get_center()-point;
	double r = circle.get_radius();
	return diff.norm_sq()-r*r<1e-6; 
}






/* Input parameters for main not checked */
int main(int argc, char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	
	std::string line;
	double center[2]={0.0,0.0};
	double radius=0.0;
	double point[2]={0.0,0.0};
	
	char word[50];
	int matched=0;
	
	char * myString = new char[300];
	while( std::getline(ifs,line) ){
		std::strcpy(myString,line.c_str());
		matched = sscanf(myString, "%s (%lf,%lf); %s %lf; %s (%lf,%lf)\n",word,&center[0],&center[1],word,&radius,word,&point[0],&point[1]);
		if(matched!=8){
			std::cout << "Error parsing data. Aborting..."<<std::endl;
			return 1;
		}
		std::cout << std::boolalpha<< point_in_circle(Point2D(point), Circle(Point2D(center),radius)) << std::endl;
	}
	
	
	//clean up
	delete[] myString;
	ifs.close();
	return 0;
}