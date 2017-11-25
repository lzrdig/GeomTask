#include "stdafx.h"
#include "Cylinder.h"

namespace SimpleGL
{
	const double PI = 3.14159;

	Cylinder::Cylinder()
	{
		m_dRadius = 0;
		m_dHeight = 0;
		m_dTilt = 0;
		m_BottomPt = { 0,0,0 };
		m_TopPt = { 0,0,0 };
	}

	Cylinder::~Cylinder()
	{
	}


	Cylinder::Cylinder(double r, double h)
	{// The base is assumed to be centered at (0,0,0)
		m_dRadius = r;
		m_dHeight = h;
	}

	Cylinder::Cylinder(double r, Point3D bottomPt, Point3D topPt)
	{// The base is assumed to be centered at (0,0,0)
		m_dRadius = r;
		m_dHeight = sqrt((bottomPt.x - topPt.x)*(bottomPt.x - topPt.x) + (bottomPt.y - topPt.y)*(bottomPt.y - topPt.y) + (bottomPt.z - topPt.z)*(bottomPt.z - topPt.z));
	}

	// Accessors
	double Cylinder::getRadius()
	{
		return m_dRadius;
	}
	double Cylinder::getHeight()
	{
		return m_dHeight;
	}
	Point3D Cylinder::getBottomCenter()
	{
		return m_BottomPt;
	}
	Point3D Cylinder::getTopCenter()
	{
		return m_TopPt;
	}

	// Setters
	void Cylinder::setRadius(double r)
	{
		m_dRadius = r;
	}
	void Cylinder::setHeight(double h)
	{
		m_dHeight = h;
	}
	void Cylinder::setBottomPt(Point3D bottomPt)
	{
		m_BottomPt = bottomPt;
	}
	void Cylinder::setTopPt(Point3D topPt)
	{
		m_TopPt = topPt;
	}

	// Calculations 
	double Cylinder::area()
	{
		return volume() * 2 * PI * m_dRadius * m_dRadius;
	}
	double Cylinder::volume()
	{
		return PI * m_dRadius * m_dRadius * m_dHeight;
	}
	bool Cylinder::Is3DpointInside(Point3D dPoint)
	{
		return false;
	}
	double Cylinder::DistanceFromPtToCyl(Point3D dPoint)
	{
		Vector3D axis;
		double axis_length = 0.0;
		double distance = 0.0;
		double off_axis_component = 0.0;
		double p_dot_axis = 0.0;
		double p_length = 0.0;
		Vector3D v1;


		axis = m_TopPt.Subtract(m_BottomPt).ConvertToVector3D();

		axis_length = axis.Norm();

		if (axis_length == 0.0)
		{
			distance = -((double)INFINITY);
			return distance;
		}


		axis.x = axis.x / (float)axis_length;

		p_dot_axis = 0.0;

		p_dot_axis = p_dot_axis
			+ (dPoint.x - m_BottomPt.x) * axis.x
			+ (dPoint.y - m_BottomPt.y) * axis.y
			+ (dPoint.z - m_BottomPt.z) * axis.z;

		//
		//  Case 1: Below bottom cap.
		//
		if (p_dot_axis <= 0.0)
		{
			distance = disk2point_dist_3d(m_BottomPt, m_dRadius, axis, dPoint);
		}

		//
		//  Case 2: between cylinder planes.
		//
		else if (p_dot_axis <= axis_length)
		{

			v1 = dPoint.Subtract(m_BottomPt).ConvertToVector3D();

			p_length = v1.Norm();
			off_axis_component = sqrt(pow(p_length, 2) - pow(p_dot_axis, 2));

			distance = off_axis_component - m_dRadius;

			if (distance < 0.0)
			{
				distance = distance > p_dot_axis - axis_length ? distance : p_dot_axis - axis_length;
				distance = distance > -p_dot_axis ? distance : -p_dot_axis;
			}
		}

		//
		//  Case 3: Above the top cap.
		//
		else if (axis_length < p_dot_axis)
		{
			distance = disk2point_dist_3d(m_TopPt, m_dRadius, axis, dPoint);
		}

		return distance;
	}


	double Cylinder::disk2point_dist_3d(Point3D pc, double r, Vector3D axis, Point3D p)
		//****************************************************************************80
		//
		//  Purpose:
		//
		//    DISK_POINT_DIST_3D determines the distance from a disk to a point in 3D.
		//
		//  Discussion:
		//
		//    A disk in 3D satisfies the equations:
		//
		//      ( P(1) - PC(1) )^2 + ( P(2) - PC(2) )^2 + ( P(3) - PC(3) <= R^2
		//
		//    and
		//
		//      P(1) * AXIS(1) + P(2) * AXIS(2) + P(3) * AXIS(3) = 0
		//
		//  Parameters:
		//
		//    Input, double PC(3), the center of the disk.
		//
		//    Input, double R, the radius of the disk.
		//
		//    Input, double AXIS(3), the axis vector.
		//
		//    Input, double P(3), the point to be checked.
		//
		//    Output, double DISK2POINT_DIST_3D, the distance of the
		//    point to the disk.
		//
	{
		double axial_component;
		double axis_length;
		double dist;
		double off_axis_component;
		Point3D off_axis;
		Vector3D v;

		//
		//  Special case: the point is the center.
		//
		if (vec_eq(p, pc))
		{
			dist = 0.0;
			return dist;
		}

		axis_length = axis.Norm();

		if (axis_length <= 0.0)
		{
			dist = -((double)INFINITY);
			return dist;
		}


		v = p.Subtract(pc).ConvertToVector3D();


		axial_component = vec_dot_product(v, axis) / axis_length;
		//
		//  Special case: the point satisfies the disk equation exactly.
		//
		if (v.Norm() <= r && axial_component == 0.0)
		{
			dist = 0.0;
			return dist;
		}
		//
		//  Decompose P-PC into axis component and off-axis component.
		//
		auto tmp = axis.DivideByScalar(axis_length).MultiplyByScalar(axial_component);
		off_axis = p.Subtract(pc).SubtractVector(axis.DivideByScalar(axis_length).MultiplyByScalar(axial_component));

		off_axis_component = off_axis.ConvertToVector3D().Norm();
		//
		//  If the off-axis component has norm less than R, the nearest point is
		//  the projection to the disk along the axial direction, and the distance
		//  is just the dot product of P-PC with unit AXIS.
		//
		if (off_axis_component <= r)
		{
			dist = fabs(axial_component);
			return dist;
		}
		//
		//  Otherwise, the nearest point is along the perimeter of the disk.
		//
		dist = sqrt(pow(axial_component, 2)	+ pow(off_axis_component - r, 2));

		return dist;
	}

	double Cylinder::vec_dot_product(Vector3D a1, Vector3D a2)
	{
		double value = 0.0;

		value = value + a1.x * a2.x + a1.y * a2.y + a1.z * a2.z;

		return value;
	}

	bool Cylinder::vec_eq(Point3D a1, Point3D a2)
	{
		if (a1.x == a2.x && a1.y == a2.y && a1.z == a2.z)
		{
			return true;
		}

		return false;
	}


}