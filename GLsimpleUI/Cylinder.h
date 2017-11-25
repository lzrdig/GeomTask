#pragma once

#include "MathUtils.h"

namespace SimpleGL
{
class Cylinder
{
public:
	~Cylinder();

	// Constructors
	Cylinder();
	Cylinder(double r, double h);
	//Cylinder(double r, double h, Point3D bottomPt);
	//Cylinder(double r, double h, Point3D bottomPt, Angle3D tilt);
	Cylinder(double r, Point3D bottomPt, Point3D topPt);

	// Accessors
	double getRadius();
	double getHeight();
	Point3D getBottomCenter();
	Point3D getTopCenter();
	void setRadius(double r);
	void setHeight(double h);
	void setBottomPt(Point3D bottomPt);
	void setTopPt(Point3D topPt);
	double area();
	double volume();

	// 
	bool Is3DpointInside(Point3D dPoint);
	double DistanceFromPtToCyl(Point3D dPoint);
	double disk2point_dist_3d(Point3D pc, double r, Vector3D axis, Point3D p);
	double vec_dot_product(Vector3D a1, Vector3D a2);
	bool vec_eq(Point3D a1, Point3D a2);

private:
	double m_dRadius;
	double m_dHeight;
	Point3D m_BottomPt;
	Point3D m_TopPt;
	double m_dTilt;
};

}