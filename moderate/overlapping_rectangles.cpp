#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

/*Challenge description: 
https://www.codeeval.com/open_challenges/70/
*/


/*2D poit class */
class Point2D{
private:
	double x;
	double y;
public:
	Point2D():x(0.0),y(0.0){};
	Point2D(double X, double Y):x(X),y(Y){};
	~Point2D(){};
	void set_x(double X){x=X;};
	void set_y(double Y){y=Y;};
	double get_x() const {return x;};
	double get_y() const {return y;};
	Point2D& operator=(const Point2D&);
	void print();
};


Point2D& Point2D::operator=(const Point2D& B){
	this->x=B.get_x();
	this->y=B.get_y();
	return *this;
}

Point2D operator-(const Point2D& A, const Point2D& B){
	double x = A.get_x()-B.get_x();
	double y = A.get_y()-B.get_y();
	return Point2D(x,y);
}

void Point2D::print(){
	std::cout << "Point = ("<<x<<","<<y<<")"<<std::endl;
}


/* Rectangle Class */
class Rectangle{
private:
	double l;
	double h;
	Point2D origin;
public:
	Rectangle():l(0.0),h(0.0),origin(Point2D(0,0)){};
	Rectangle(double L, double H, Point2D C):l(L),h(H),origin(C){};
	Rectangle(Point2D Ul, Point2D Lr);
	~Rectangle(){};
	Point2D get_origin() const;
	double get_h() const{return h;};
	double get_l() const{return l;};
	void print();
	bool contains(const Rectangle& A);
};


Rectangle::Rectangle(Point2D Ul, Point2D Lr){
	double x = Ul.get_x();
	double y = Lr.get_y();
	l = Lr.get_x()-x;
	h = Ul.get_y()-y;
	if( l<0 || h<0 ){
		std::cout << "Faulty data, cannot build Rectangle object. Aborting..."<< std::endl;
		exit(EXIT_FAILURE);
	}
	origin = Point2D(x,y);
}

Point2D Rectangle::get_origin() const{
	return this->origin;
}

void Rectangle::print(){
	std::cout << "origin = ("<< origin.get_x()<<","<<origin.get_y()<<"), h="<<h<<", l="<<l<<std::endl;
}

bool Rectangle::contains(const Rectangle& A){
	if( get_l()<A.get_l() ){
		return false;
	}else{
		Point2D Oa = A.get_origin();
		Point2D Ob = get_origin();
		if( Oa.get_x() > Ob.get_x() && (Oa.get_x() + A.get_l()) < (Ob.get_x() + get_l()) && Oa.get_y() > Ob.get_y() && (Oa.get_y() + A.get_h()) < (Ob.get_y() + get_h()) ) {
			return true;
		}else{
			return false;
		}
		
	}
}

/* Returns truw of rectangles A and B overlap */
bool overlap(Rectangle A, Rectangle B){
	Point2D Aorigin = A.get_origin();
	Point2D Borigin = B.get_origin();
	if (Aorigin.get_y() > Borigin.get_y()+B.get_h() || Borigin.get_y() > Aorigin.get_y()+A.get_h() ){ //one rectangle is to the left/right of the other
		return false;
	}else if( Aorigin.get_x() > Borigin.get_x()+B.get_l() || Borigin.get_x() > Aorigin.get_x()+A.get_l()){//one rectangle is above/under the other
		return false;
	}else if( A.contains(B) || B.contains(A) ){ //one rectangle is inside the other: they overlap as a surface but not as a polygon
		return false;
	}else{
		return true;
	}
}


/*Auxiliary function to check Rectangle object has been built correctly */
void health_check(Rectangle R,double Ax,double Ay,double Bx,double By){
	Point2D c = R.get_origin();
	if( c.get_x()+R.get_l() == Bx && c.get_y() == By && c.get_y()+R.get_h() == Ay && c.get_x() == Ax){
		//do nothing
	}else{
		std::cout << "Error building rectangle: health check failed. Aborting..."<<std::endl;
		exit(EXIT_FAILURE);
	}
}


/*Main program */
int main(int argc , char ** argv){
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(!ifs.is_open()){
		return 1;
	}
	
	
	std::string line;
	char * cstring;
	double Ax,Ay,Bx,By,Cx,Cy,Dx,Dy;
	int flag;
	
	while(std::getline(ifs,line)){
		cstring = (char *)line.c_str();
		flag=sscanf(cstring,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&Ax,&Ay,&Bx,&By,&Cx,&Cy,&Dx,&Dy);
		if(flag!=8){
			std::cout<< "error reading input data. Aborting..."<<std::endl;
			return 1;
		}
		Rectangle AB(Point2D(Ax,Ay),Point2D(Bx,By));
		Rectangle CD(Point2D(Cx,Cy),Point2D(Dx,Dy));
		
		/*============================*/
		//bool result = !(Ax > Dx || Ay < Dy || Cx > Bx || Cy < By);
		//std::cout << std::boolalpha << result << std::endl;
		/*============================*/
		if (overlap(AB,CD)){
			std::cout << "True";
		}else{
			std::cout << "False";
		}
		std::cout << std::endl;
	}
	
	//clean up
	ifs.close();
	return 0;
}