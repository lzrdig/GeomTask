#pragma once

#include "CommonDeclares.h"

extern "C" __declspec(dllexport) double __cdecl GetDistFromPtToCylinder(double radius,
	double bottomX, double bottomY, double bottomZ,
	double topX, double topY, double topZ,
	double ptX, double ptY, double ptZ
);

namespace GeomTask
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
		double GetRadius();
		double GetHeight();
		Point3D GetBottomPt();
		Point3D GetTopPt();
		void SetRadius(double r);
		void SetHeight(double h);
		double Area();
		double Volume();
		Point3D GetFoundPt();

		// 
		bool Is3DpointInside(Point3D dPoint);
		double DistanceFromPtToCyl(Point3D dPoint);
		Point3D ConvertToPoint3D(Vector3D vec);
		Vector3D ConvertToVector3D(Point3D pt);
		Point3D SubtractVectorFromPoint(Point3D pt, Vector3D vec);
		Vector3D SubtractPointFromVector(Vector3D vec, Point3D pt);


	private:
		double m_dRadius;
		double m_dHeight;
		Point3D m_BottomPt;
		Point3D m_TopPt;
		double m_dTilt;

		Point3D m_FoundPt;

		double Disk2point_dist_3d(Point3D pc, double r, Vector3D axis, Point3D p);
		double* cylinder_point_near_3d(double p1[3], double p2[3], double r, double p[3]);
		void r8vec_zero(int n, double a1[]);
		double r8vec_norm(int n, double a[]);
		double* r8vec_any_normal(int dim_num, double v1[]);
	};

}