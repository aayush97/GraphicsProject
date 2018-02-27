#include <bits/stdc++.h>
#include "vectormath.h"
#include "matrix.h"
#include <SFML/Graphics.hpp>
#include "model.h"

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
	Model m;
	if(!m.loadModel("DNA.obj")){
		cout << "Obj file couldn't be opened!" << endl;
		exit(1);
	}
	vector<Vector> Modelvertices = m.v;
	vector<Vector> WorldVertices;
	// Modelvertices.push_back(Vector(0,0,0));
	// Modelvertices.push_back(Vector(100,0,0));
	// Modelvertices.push_back(Vector(0,100,0));
	// Modelvertices.push_back(Vector(0,0,100));
	// Modelvertices.push_back(Vector(100,100,0));
	// Modelvertices.push_back(Vector(100,0,100));
	// Modelvertices.push_back(Vector(0,100,100));
	// Modelvertices.push_back(Vector(100,100,100));
	Matrix r = rotateY(45);
	for(int i=0;i<Modelvertices.size();i++){
		Modelvertices[i] = r*Modelvertices[i];
	}
	vector<Vector> ProjectionVertices;
	// vector< pair<int,int> > edgeList;
	// vector< vector<int> > faces;
	// vector<int> faceBuffer;

	// faceBuffer.push_back(0);
	// faceBuffer.push_back(1);
	// faceBuffer.push_back(5);
	// faceBuffer.push_back(3);
	// faces.push_back(faceBuffer);
	// faceBuffer.clear();

	// faceBuffer.push_back(0);
	// faceBuffer.push_back(3);
	// faceBuffer.push_back(6);
	// faceBuffer.push_back(2);
	// faces.push_back(faceBuffer);
	// faceBuffer.clear();

	// faceBuffer.push_back(3);
	// faceBuffer.push_back(5);
	// faceBuffer.push_back(7);
	// faceBuffer.push_back(6);
	// faces.push_back(faceBuffer);
	// faceBuffer.clear();

	// faceBuffer.push_back(0);
	// faceBuffer.push_back(2);
	// faceBuffer.push_back(4);
	// faceBuffer.push_back(1);
	// faces.push_back(faceBuffer);
	// faceBuffer.clear();

	// faceBuffer.push_back(2);
	// faceBuffer.push_back(6);
	// faceBuffer.push_back(7);
	// faceBuffer.push_back(4);
	// faces.push_back(faceBuffer);
	// faceBuffer.clear();

	// faceBuffer.push_back(1);
	// faceBuffer.push_back(4);
	// faceBuffer.push_back(7);
	// faceBuffer.push_back(5);
	// faces.push_back(faceBuffer);
	// faceBuffer.clear();

	// vector< vector<double> > facesEquation;


	// edgeList.push_back(make_pair(0,1));
	// edgeList.push_back(make_pair(0,2));
	// edgeList.push_back(make_pair(0,3));
	// edgeList.push_back(make_pair(1,4));

	// edgeList.push_back(make_pair(1,5));
	// edgeList.push_back(make_pair(2,6));
	// edgeList.push_back(make_pair(2,4));
	// edgeList.push_back(make_pair(3,5));

	// edgeList.push_back(make_pair(3,6));
	// edgeList.push_back(make_pair(4,7));
	// edgeList.push_back(make_pair(5,7));
	// edgeList.push_back(make_pair(6,7));

	WorldCoordinateTransform WCTransform(Vector(0,0,1,1),Vector(0,1,0,1),Vector(0,0,0,1));
	Matrix WCT = WCTransform.getComposite();
	ProjectionTransformation PT(200,400);
	Matrix PPT = PT.getComposite();
	cout << Modelvertices.size() <<endl;
	for(int i=0;i<Modelvertices.size();i++){
		//cout << Modelvertices[i].x << " " << Modelvertices[i].y <<  " " << Modelvertices[i].z << endl;
		WorldVertices.push_back(WCT*Modelvertices[i]);
		//cout << WorldVertices[i].x << " " << WorldVertices[i].y <<  " " << WorldVertices[i].z << endl;
		//cout << WorldVertices[i].h << endl;
	}



	for(int i=0;i<WorldVertices.size();i++){
		ProjectionVertices.push_back(PPT*WorldVertices[i]);
		//cout << ProjectionVertices[i].x  << " " << ProjectionVertices[i].y << " " << ProjectionVertices[i].z<< endl;

	}


	cout << ProjectionVertices.size() << endl;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Wireframe");
	sf::VertexArray lines(sf::LinesStrip, 4);

	    for(int i=0;i<m.f.size();i++){
	    	double x1 = ProjectionVertices[m.f[i].v[0]].x;
	    	double y1 = ProjectionVertices[m.f[i].v[0]].y;
	    	double z1 = ProjectionVertices[m.f[i].v[0]].z;
	    	double h1 = ProjectionVertices[m.f[i].v[0]].h;
	    	double x2 = ProjectionVertices[m.f[i].v[1]].x;
	    	double y2 = ProjectionVertices[m.f[i].v[1]].y;
	    	double z2 = ProjectionVertices[m.f[i].v[1]].z;
	    	double h2 = ProjectionVertices[m.f[i].v[1]].h;
	    	double x3 = ProjectionVertices[m.f[i].v[2]].x;
	    	double y3 = ProjectionVertices[m.f[i].v[2]].y;
	    	double z3 = ProjectionVertices[m.f[i].v[2]].z;
	    	double h3 = ProjectionVertices[m.f[i].v[2]].h;
	    	x1/=h1;
	    	x2/=h2;
	    	x3/=h3;
	    	y1/=h1;
	    	y2/=h2;
	    	y3/=h3;
	    	z1/=h1;
	    	z1/=h2;
	    	z3/=h3;

	    	int xa=x1+300;
	    	int ya=y1+300;
	    	int za=z1;
	    	int xb=x2+300;
	    	int yb=y2+300;
	    	int zb=z2;
	    	int xc=x3+300;
	    	int yc=y3+300;
	    	int zc=z3;
	    	
	    	cout << xa << " " << ya  << " " << za << " " <<  xb << " " << yb << " " << zb << endl;
	    	lines[0].position = sf::Vector2f(xa,ya);
	 		lines[1].position = sf::Vector2f(xb,yb);
	 		lines[2].position = sf::Vector2f(xc,yc);
	 		lines[3].position = sf::Vector2f(xa,ya);

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