#include "stdafx.h"
#include "MathUtils.h"

namespace SimpleGL
{
	struct Point3D Point3D::Add(Point3D pt2)
	{
		Point3D res;

		res.x = x + pt2.x;
		res.y = y + pt2.y;
		res.z = z + pt2.z;

		return res;
	}

	struct Point3D Point3D::Subtract(Point3D pt2)
	{
		Point3D res;

		res.x = x - pt2.x;
		res.y = y - pt2.y;
		res.z = z - pt2.z;

		return res;
	}

	struct Point3D Point3D::SubtractVector(Vector3D vec)
	{
		Point3D res;

		res.x = x - vec.x;
		res.y = y - vec.y;
		res.z = z - vec.z;

		return res;
	}

	struct Point3D Point3D::DivideByScalar(double scale)
	{
		Point3D res;

		res.x = x / (float)scale;
		res.y = y / (float)scale;
		res.z = z / (float)scale;

		return res;
	}

	struct Point3D Point3D::MultiplyByScalar(double scale)
	{
		Point3D res;

		res.x = x * (float)scale;
		res.y = y * (float)scale;
		res.z = z * (float)scale;

		return res;
	}

	struct Vector3D Point3D::ConvertToVector3D()
	{
		Vector3D res = { 0,0,0 };

		res.x = x; res.y = y; res.z = z;

		return res;
	}
}