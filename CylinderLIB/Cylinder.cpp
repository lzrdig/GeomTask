#include "stdafx.h"
#include "Cylinder.h"

namespace GeomTask
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
		m_dTilt = 0;
		m_BottomPt = { 0,0,0 };
		m_TopPt = { 0,0,h };
	}

	Cylinder::Cylinder(double r, Point3D bottomPt, Point3D topPt)
	{// The base is assumed to be centered at (0,0,0)
		m_dRadius = r;
		m_dHeight = sqrt((bottomPt.x - topPt.x)*(bottomPt.x - topPt.x) + (bottomPt.y - topPt.y)*(bottomPt.y - topPt.y) + (bottomPt.z - topPt.z)*(bottomPt.z - topPt.z));
		m_dTilt = 0;
		m_BottomPt = bottomPt;
		m_TopPt = topPt;
	}

	// Accessors
	double Cylinder::GetRadius()
	{
		return m_dRadius;
	}
	double Cylinder::GetHeight()
	{
		return m_dHeight;
	}
	Point3D Cylinder::GetBottomPt()
	{
		return m_BottomPt;
	}
	Point3D Cylinder::GetTopPt()
	{
		return m_TopPt;
	}
	Point3D Cylinder::GetFoundPt()
	{
		return m_FoundPt;
	}

	// Setters
	void Cylinder::SetRadius(double r)
	{
		m_dRadius = r;
	}
	void Cylinder::SetHeight(double h)
	{
		m_dHeight = h;
	}

	// Calculations 
	double Cylinder::Area()
	{
		return 2 * PI * m_dRadius * m_dHeight + 2 * PI * m_dRadius * m_dRadius;
	}
	double Cylinder::Volume()
	{
		return PI * m_dRadius * m_dRadius * m_dHeight;
	}

	bool Cylinder::Is3DpointInside(Point3D dTestPoint)
	{// pt1 and pt2 are the cyl top and bottom center points in the comments
		double dx, dy, dz;		// vector d  from line segment pt1 to pt2
		double pdx, pdy, pdz;	// vector pd from pt1 to test point "dTestPoint"
		double dot, dsq, lengthsq;

		lengthsq = (m_dHeight*m_dHeight);
		dsq = (m_dRadius*m_dRadius);

		dx = m_TopPt.x - m_BottomPt.x;	// translate so pt1 is origin.  Make vector from
		dy = m_TopPt.y - m_BottomPt.y;  // pt1 to pt2.  Need for this is easily eliminated
		dz = m_TopPt.z - m_BottomPt.z;

		pdx = dTestPoint.x - m_BottomPt.x;		// vector from pt1 to test point.
		pdy = dTestPoint.y - m_BottomPt.y;
		pdz = dTestPoint.z - m_BottomPt.z;

		// Dot the d and pd vectors to see if point lies behind the 
		// cylinder cap at pt1.x, pt1.y, pt1.z

		dot = pdx * dx + pdy * dy + pdz * dz;

		// If dot is less than zero the point is behind the pt1 cap.
		// If greater than the cylinder height sqared
		// then the point is outside the other end cap at pt2.

		if (dot < 0.0f || dot > lengthsq)
		{
			return false;
		}
		else
		{	// the test point is in between the caps
			// distance squared to the cylinder axis:
			dsq = ((pdx*pdx + pdy*pdy + pdz*pdz) - dot*dot / m_dHeight);

			if (dsq > lengthsq)
				return false;
			else 
				return true;

		}
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
		Point3D foundPt{ 0.0,0.0,0.0 };
		double* v2;

		// find vector corrsponding to the axis of the cylinder
		axis = ConvertToVector3D(m_TopPt.Subtract(m_BottomPt));

		axis_length = axis.Norm();

		if (axis_length == 0.0)
		{
			distance = -((double)INFINITY);
			return distance;
		}

		axis = axis.DivideByScalar(axis_length);

		// find the scalar product of the vector connecting 
		// the test point and the bottom of the cylinder (diff vector)
		// multiplied by the cylinder axis vector
		p_dot_axis = 0.0;

		p_dot_axis = p_dot_axis
			+ (dPoint.x - m_BottomPt.x) * axis.x
			+ (dPoint.y - m_BottomPt.y) * axis.y
			+ (dPoint.z - m_BottomPt.z) * axis.z;

		//
		//  Case 1: Below bottom cap. (diff vector is perpendicular to the axis vector) 
		//
		if (p_dot_axis <= 0.0)
		{
			distance = Disk2point_dist_3d(m_BottomPt, m_dRadius, axis, dPoint);
		}

		//
		//  Case 2: between cylinder planes.
		//
		else if (p_dot_axis <= axis_length)
		{
			v1 = ConvertToVector3D(dPoint.Subtract(m_BottomPt));

			p_length = v1.Norm();
			off_axis_component = sqrt(p_length*p_length - p_dot_axis*p_dot_axis);

			distance = off_axis_component - m_dRadius;

			if (distance < 0.0)
			{
				distance = distance > p_dot_axis - axis_length ? distance : p_dot_axis - axis_length;
				distance = distance > -p_dot_axis ? distance : -p_dot_axis;
			}

			m_FoundPt = ConvertToPoint3D(ConvertToVector3D(m_BottomPt).Add(axis.MultiplyByScalar(p_dot_axis / axis_length)));
		}

		//
		//  Case 3: Above the top cap.
		//
		else if (axis_length < p_dot_axis)
		{
			distance = Disk2point_dist_3d(m_TopPt, m_dRadius, axis, dPoint);
		}

		double p1[3], p2[3], p[3];
		p1[0] = m_BottomPt.x;
		p1[1] = m_BottomPt.y;
		p1[2] = m_BottomPt.z;
		p2[0] = m_TopPt.x;
		p2[1] = m_TopPt.y;
		p2[2] = m_TopPt.z;
		p[0] = dPoint.x;
		p[1] = dPoint.y;
		p[2] = dPoint.z;

		v2 = cylinder_point_near_3d(p1, p2, m_dRadius, p);

		m_FoundPt.x = v2[0];
		m_FoundPt.y = v2[1];
		m_FoundPt.z = v2[2];

		return distance;
	}


	// Helpers
	double Cylinder::Disk2point_dist_3d(Point3D pc, double r, Vector3D axis, Point3D p)

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
		//    Input, double PC[3], the center of the disk.
		//
		//    Input, double R, the radius of the disk.
		//
		//    Input, double AXIS[3], the axis vector - which is the normal to the disk.
		//
		//    Input, double P[3], the point to be checked.
		//
		//    Output, double DISK2POINT_DIST_3D, the distance of the
		//    point to the disk.
		//
		//  Licensing:
		//
		//    This code is distributed under the GNU LGPL license.
		//
		//  Modified:
		//
		//    23 August 2005
		//	  15 November 2017		
		//
		//  Author:
		//
		//    John Burkardt
		//  Modifications introduced by Dorel Guzun (use of Point3D and Vector3D structs for better reading)
		//
		//  Parameters:
		//
		//    Input, double P1[3], P2[3], the first and last points
		//    on the axis line of the cylinder.
		//
		//    Input, double R, the radius of the cylinder.
		//
		//    Input, double P[3], the point.
		//
		//    Output, double CYLINDER_POINT_DIST_3D, the distance from the point
		//    to the cylinder.
		//
	{
		double axial_component;
		double axis_length;
		double dist;
		double off_axis_component;
		Point3D off_axis;
		Vector3D v;
		Vector3D tmp;

		//
		//  Special case: the point is the center.
		//
		if (p.IsEqual(pc))
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


		v = ConvertToVector3D(p.Subtract(pc));


		axial_component = v.DotProduct(axis) / axis_length;

		m_FoundPt = m_TopPt;

		//
		//  Special case: the point satisfies the disk equation exactly.
		//
		if (v.Norm() <= r && axial_component == 0.0)
		{
			dist = 0.0;
			m_FoundPt = pc;
			return dist;
		}
		//
		//  Decompose P-PC into axis component and off-axis component.
		//
		tmp = axis.DivideByScalar(axis_length).MultiplyByScalar(axial_component);
		off_axis = ConvertToPoint3D( SubtractPointFromVector(tmp, p.Subtract(pc)));


		off_axis_component = ConvertToVector3D(off_axis).Norm();
		//
		//  If the off-axis component has norm less than R, the nearest point is
		//  the projection to the disk along the axial direction, and the distance
		//  is just the dot product of P-PC with unit AXIS.
		//
		if (off_axis_component <= r)
		{
			dist = fabs(axial_component);

			m_FoundPt = ConvertToPoint3D(ConvertToVector3D(p).Subtract(tmp));
			return dist;
		}
		//
		//  Otherwise, the nearest point is along the perimeter of the disk.
		//
		dist = sqrt(pow(axial_component, 2)	+ pow(off_axis_component - r, 2));

		double delta = off_axis_component - r;
		tmp = ConvertToVector3D(off_axis).DivideByScalar(off_axis_component).MultiplyByScalar(delta);
		m_FoundPt = ConvertToPoint3D(tmp);

		return dist;
	}

	Point3D Cylinder::ConvertToPoint3D(Vector3D vec)
	{
		Point3D res{ 0.0,0.0,0.0 };

		res.x = vec.x;
		res.y = vec.y;
		res.z = vec.z;

		return res;
	}

	Vector3D Cylinder::ConvertToVector3D(Point3D pt)
	{
		Vector3D res = { 0,0,0 };

		res.x = pt.x; 
		res.y = pt.y; 
		res.z = pt.z;

		return res;
	}

	Point3D Cylinder::SubtractVectorFromPoint(Point3D pt, Vector3D vec)
	{
		Point3D res;

		res.x = pt.x - vec.x;
		res.y = pt.y - vec.y;
		res.z = pt.z - vec.z;

		return res;
	}

	Vector3D Cylinder::SubtractPointFromVector(Vector3D vec, Point3D pt)
	{
		Vector3D res;

		res.x = vec.x - pt.x;
		res.y = vec.y - pt.y;
		res.z = vec.z - pt.z;

		return res;
	}


// Code borrowed from John Burkardt
	double* Cylinder::cylinder_point_near_3d(double p1[3], double p2[3], double r, double p[3])
		//****************************************************************************80
		//
		//  Purpose:
		//
		//    CYLINDER_POINT_NEAR_3D: nearest point on a cylinder to a point in 3D.
		//
		//  Discussion:
		//
		//    We are computing the nearest point on the SURFACE of the cylinder.
		//
		//    The surface of a (right) (finite) cylinder in 3D is defined by an axis,
		//    which is the line segment from point P1 to P2, and a radius R.  The points
		//    on the surface of the cylinder are:
		//    * points at a distance R from the line through P1 and P2, and whose nearest
		//      point on the line through P1 and P2 is strictly between P1 and P2,
		//    PLUS
		//    * points at a distance less than or equal to R from the line through P1
		//      and P2, whose nearest point on the line through P1 and P2 is either
		//      P1 or P2.
		//
		//  Licensing:
		//
		//    This code is distributed under the GNU LGPL license.
		//
		//  Modified:
		//
		//    19 August 2005
		//
		//  Author:
		//
		//    John Burkardt
		//
		//  Parameters:
		//
		//    Input, double P1[3], P2[3], the first and last points
		//    on the axis line of the cylinder.
		//
		//    Input, double R, the radius of the cylinder.
		//
		//    Input, double P[3], the point.
		//
		//    Output, double CYLINDER_POINT_NEAR_3D[3], the nearest point on the cylinder.
		//
	{
# define DIM_NUM 3

		double axial_component;
		double axis[DIM_NUM];
		double axis_length;
		double distance;
		int i;
		double *normal;
		double off_axis[DIM_NUM];
		double off_axis_component;
		double *pn;

		pn = new double[DIM_NUM];

		for (i = 0; i < DIM_NUM; i++)
		{
			axis[i] = p2[i] - p1[i];
		}
		axis_length = r8vec_norm(DIM_NUM, axis);
		for (i = 0; i < DIM_NUM; i++)
		{
			axis[i] = axis[i] / axis_length;
		}

		axial_component = 0.0;
		for (i = 0; i < DIM_NUM; i++)
		{
			axial_component = axial_component + (p[i] - p1[i]) * axis[i];
		}
		for (i = 0; i < DIM_NUM; i++)
		{
			off_axis[i] = p[i] - p1[i] - axial_component * axis[i];
		}

		off_axis_component = r8vec_norm(DIM_NUM, off_axis);
		//
		//  Case 1: Below bottom cap.
		//
		if (axial_component <= 0.0)
		{
			if (off_axis_component <= r)
			{
				for (i = 0; i < DIM_NUM; i++)
				{
					pn[i] = p1[i] + off_axis[i];
				}
			}
			else
			{
				for (i = 0; i < DIM_NUM; i++)
				{
					pn[i] = p1[i] + (r / off_axis_component) * off_axis[i];
				}
			}
		}
		//
		//  Case 2: between cylinder planes.
		//
		else if (axial_component <= axis_length)
		{
			if (off_axis_component == 0.0)
			{
				normal = r8vec_any_normal(DIM_NUM, axis);
				for (i = 0; i < DIM_NUM; i++)
				{
					pn[i] = p[i] + r * normal[i];
				}
				delete[] normal;
			}
			else
			{
				distance = fabs(off_axis_component - r);

				for (i = 0; i < DIM_NUM; i++)
				{
					pn[i] = p1[i] + axial_component * axis[i]
						+ (r / off_axis_component) * off_axis[i];
				}
				if (off_axis_component < r)
				{
					if (axis_length - axial_component < distance)
					{
						distance = axis_length - axial_component;
						for (i = 0; i < DIM_NUM; i++)
						{
							pn[i] = p2[i] + off_axis[i];
						}
					}
					if (axial_component < distance)
					{
						distance = axial_component;
						for (i = 0; i < DIM_NUM; i++)
						{
							pn[i] = p1[i] + off_axis[i];
						}
					}
				}
			}
		}
		//
		//  Case 3: Above the top cap.
		//
		else if (axis_length < axial_component)
		{
			if (off_axis_component <= r)
			{
				for (i = 0; i < DIM_NUM; i++)
				{
					pn[i] = p2[i] + off_axis[i];
				}
			}
			else
			{
				for (i = 0; i < DIM_NUM; i++)
				{
					pn[i] = p2[i] + (r / off_axis_component) * off_axis[i];
				}
			}
		}

		return pn;
# undef DIM_NUM
	}

	void Cylinder::r8vec_zero(int n, double a1[])

		//****************************************************************************80
		//
		//  Purpose:
		//
		//    R8VEC_ZERO zeroes an R8VEC.
		//
		//  Licensing:
		//
		//    This code is distributed under the GNU LGPL license.
		//
		//  Modified:
		//
		//    03 July 2005
		//
		//  Author:
		//
		//    John Burkardt
		//
		//  Parameters:
		//
		//    Input, int N, the number of entries in the vectors.
		//
		//    Output, double A1[N], a vector of zeroes.
		//
	{
		int i;

		for (i = 0; i < n; i++)
		{
			a1[i] = 0.0;
		}
		return;
	}

	double Cylinder::r8vec_norm(int n, double a[])

		//****************************************************************************80
		//
		//  Purpose:
		//
		//    R8VEC_NORM returns the L2 norm of an R8VEC.
		//
		//  Discussion:
		//
		//    An R8VEC is a vector of R8's.
		//
		//    The vector L2 norm is defined as:
		//
		//      R8VEC_NORM = sqrt ( sum ( 1 <= I <= N ) A(I)^2 ).
		//
		//  Licensing:
		//
		//    This code is distributed under the GNU LGPL license.
		//
		//  Modified:
		//
		//    01 March 2003
		//
		//  Author:
		//
		//    John Burkardt
		//
		//  Parameters:
		//
		//    Input, int N, the number of entries in A.
		//
		//    Input, double A[N], the vector whose L2 norm is desired.
		//
		//    Output, double R8VEC_NORM, the L2 norm of A.
		//
	{
		int i;
		double v;

		v = 0.0;

		for (i = 0; i < n; i++)
		{
			v = v + a[i] * a[i];
		}
		v = sqrt(v);

		return v;
	}

	double* Cylinder::r8vec_any_normal(int dim_num, double v1[])
		//****************************************************************************80
		//
		//  Purpose:
		//
		//    R8VEC_ANY_NORMAL returns some normal vector to V1.
		//
		//  Discussion:
		//
		//    If DIM_NUM < 2, then no normal vector can be returned.
		//
		//    If V1 is the zero vector, then any unit vector will do.
		//
		//    No doubt, there are better, more robust algorithms.  But I will take
		//    just about ANY reasonable unit vector that is normal to V1.
		//
		//  Licensing:
		//
		//    This code is distributed under the GNU LGPL license.
		//
		//  Modified:
		//
		//    23 August 2005
		//
		//  Author:
		//
		//    John Burkardt
		//
		//  Parameters:
		//
		//    Input, int DIM_NUM, the spatial dimension.
		//
		//    Input, double V1[DIM_NUM], the vector.
		//
		//    Output, double R8VEC_ANY_NORMAL[DIM_NUM], a vector that is
		//    normal to V2, and has unit Euclidean length.
		//
	{
		int i;
		int j;
		int k;
		double *v2;
		double vj;
		double vk;

		v2 = new double[dim_num];

		if (dim_num < 2)
		{
			v2[0] = 0.0;
			return v2;
		}		

		if (r8vec_norm(dim_num, v1) == 0.0)
		{
			r8vec_zero(dim_num, v2);
			v2[0] = 1.0;
			return v2;
		}
		//
		//  Seek the largest entry in V1, VJ = V1(J), and the
		//  second largest, VK = V1(K).
		//
		//  Since V1 does not have zero norm, we are guaranteed that
		//  VJ, at least, is not zero.
		//
		j = -1;
		vj = 0.0;

		k = -1;
		vk = 0.0;

		for (i = 0; i < dim_num; i++)
		{
			if (fabs(vk) < fabs(v1[i]) || k == -1)
			{
				if (fabs(vj) < fabs(v1[i]) || j == -1)
				{
					k = j;
					vk = vj;
					j = i;
					vj = v1[i];
				}
				else
				{
					k = i;
					vk = v1[i];
				}
			}
		}
		//
		//  Setting V2 to zero, except that V2(J) = -VK, and V2(K) = VJ,
		//  will just about do the trick.
		//
		r8vec_zero(dim_num, v2);

		v2[j] = -vk / sqrt(vk * vk + vj * vj);
		v2[k] = vj / sqrt(vk * vk + vj * vj);

		return v2;
	}
}