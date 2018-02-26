#include <bits/stdc++.h>
#include "vectormath.h"
#include "matrix.h"
#include <SFML/Graphics.hpp>
using namespace std;

const double PI = 3.14159265359;

Matrix rotateZ(double theta){
	theta = theta*PI/180;
	Matrix m = Matrix::createIdentity(4);
	m(0,0) = cos(theta);
	m(0,1) = -sin(theta);
	m(1,0) = sin(theta);
	m(1,1) = cos(theta);
	return m;
}

Matrix rotateX(double theta){
	theta = theta*PI/180;
	Matrix m = Matrix::createIdentity(4);
	m(1,1) = cos(theta);
	m(1,2) = -sin(theta);
	m(2,1) = sin(theta);
	m(2,2) = cos(theta);
	return m;
}

Matrix rotateY(double theta){
	theta = theta*PI/180;
	Matrix m = Matrix::createIdentity(4);
	m(2,2) = cos(theta);
	m(2,0) = -sin(theta);
	m(0,2) = sin(theta);
	m(0,0) = cos(theta);
	return m;
}

Matrix scale(double factor){
	Matrix m = Matrix::createIdentity(4);
	m(0,0) = factor;
	m(1,1) = factor;
	m(2,2) = factor;
	return m;
}

Matrix translate(double tx, double ty, double tz){
	Matrix m = Matrix::createIdentity(4);
	m(0,3)=tx;
	m(1,3)=ty;
	m(2,3)=tz;
	return m;
}



class WorldCoordinateTransform{
private:
	Matrix composite;
	Vector normal;
	Vector viewUp;
	Vector xAxis;
	Vector cameraPosition;
public:
	WorldCoordinateTransform(Vector normal, Vector viewUp, Vector cameraPosition){
		xAxis = cross(normal,viewUp);
		normal.normalize();
		xAxis.normalize();
		viewUp = cross(normal,xAxis);
		composite = Matrix::createIdentity(4);
		Matrix t1 = Matrix::createIdentity(4);
		t1(0,3) -= cameraPosition.x/cameraPosition.h;
		t1(1,3) -= cameraPosition.y/cameraPosition.h;
		t1(2,3) -= cameraPosition.z/cameraPosition.h;
		Matrix t2 = Matrix::createIdentity(4);
		t2(0,0) = xAxis.x;
		t2(0,1) = xAxis.y;
		t2(0,2) = xAxis.z;
		t2(1,0) = viewUp.x;
		t2(1,1) = viewUp.y;
		t2(1,2) = viewUp.z;
		t2(2,0) = normal.x;
		t2(2,1) = normal.y;
		t2(2,2) = normal.z;
		composite = t2*t1;
	}

	Matrix& getComposite(){
		return composite;
	}
};

class ProjectionTransformation{
private:
	Matrix composite;
	double viewPlane;
	double vanishingPoint;
public:
	ProjectionTransformation(double zvp, double zprp):viewPlane(zvp),vanishingPoint(zprp){
		composite = Matrix::createIdentity(4);
		double d = zprp-zvp;
		composite(2,2) = (-zvp/d);
		composite(2,3) = (zvp*zprp/d);
		composite(3,2) = (-1/d);
		composite(3,3) = (zprp/d);

	}
	Matrix& getComposite(){
		return composite;
	}
};






int main() {
	vector<Vector> Modelvertices;
	vector<Vector> WorldVertices;
	Modelvertices.push_back(Vector(0,0,0));
	Modelvertices.push_back(Vector(100,0,0));
	Modelvertices.push_back(Vector(0,100,0));
	Modelvertices.push_back(Vector(0,0,100));
	Modelvertices.push_back(Vector(100,100,0));
	Modelvertices.push_back(Vector(100,0,100));
	Modelvertices.push_back(Vector(0,100,100));
	Modelvertices.push_back(Vector(100,100,100));
	Matrix m = rotateX(90);
	for(int i=0;i<Modelvertices.size();i++){
		Modelvertices[i] = m*Modelvertices[i];
	}
	vector<Vector> ProjectionVertices;
	vector< pair<int,int> > edgeList;
	edgeList.push_back(make_pair(0,1));
	edgeList.push_back(make_pair(0,2));
	edgeList.push_back(make_pair(0,3));
	edgeList.push_back(make_pair(1,4));

	edgeList.push_back(make_pair(1,5));
	edgeList.push_back(make_pair(2,6));
	edgeList.push_back(make_pair(2,4));
	edgeList.push_back(make_pair(3,5));

	edgeList.push_back(make_pair(3,6));
	edgeList.push_back(make_pair(4,7));
	edgeList.push_back(make_pair(5,7));
	edgeList.push_back(make_pair(6,7));

	WorldCoordinateTransform WCTransform(Vector(0,0,1,1),Vector(0,1,0,1),Vector(50,50,-50,1));
	Matrix WCT = WCTransform.getComposite();
	ProjectionTransformation PT(-100,-400);
	Matrix PPT = PT.getComposite();

	for(int i=0;i<Modelvertices.size();i++){
		WorldVertices.push_back(WCT*Modelvertices[i]);
	}

	for(int i=0;i<WorldVertices.size();i++){
		ProjectionVertices.push_back(PPT*WorldVertices[i]);

	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "Wireframe");
	sf::VertexArray lines(sf::LinesStrip, 2);
	    for(int i=0;i<12;i++){
	    	double x1 = ProjectionVertices[edgeList[i].first].x;
	    	double y1 = ProjectionVertices[edgeList[i].first].y;
	    	double h1 = ProjectionVertices[edgeList[i].first].h;
	    	double x2 = ProjectionVertices[edgeList[i].second].x;
	    	double y2 = ProjectionVertices[edgeList[i].second].y;
	    	double h2 = ProjectionVertices[edgeList[i].second].h;
	    	x1/=h1;
	    	x2/=h2;
	    	y1/=h1;
	    	y2/=h2;
	    	int xa=x1*2+300;
	    	int ya=y1*2+300;
	    	int xb=x2*2+300;
	    	int yb=y2*2+300;
	    	
	    	cout << xa << " " << ya  << " " << xb << " " << yb << endl;
	    	lines[0].position = sf::Vector2f(xa,ya);
	 		lines[1].position = sf::Vector2f(xb,yb);

	 		window.draw(lines);
	    }
	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.display();
    }

    return 0;
	    
 	

	
}