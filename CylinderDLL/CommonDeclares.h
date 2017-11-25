#pragma once

namespace GeomTask
{
	struct Vector3D {
		double x;
		double y;
		double z;

		double Norm()
		{
			double v = 0.0;

			v = v
				+ x * x
				+ y * y
				+ z * z
				;

			v = sqrt(v);

			return v;
		}

		Vector3D Add(Vector3D vec2)
		{
			Vector3D res;

			res.x = x + vec2.x;
			res.y = y + vec2.y;
			res.z = z + vec2.z;

			return res;
		}

		Vector3D Subtract(Vector3D vec2)
		{
			Vector3D res;

			res.x = x - vec2.x;
			res.y = y - vec2.y;
			res.z = z - vec2.z;

			return res;
		}

		double DotProduct(Vector3D vec2)
		{
			Vector3D tmp;
			double res;

			tmp.x = x * vec2.x;
			tmp.y = y * vec2.y;
			tmp.z = z * vec2.z;

			res = tmp.x + tmp.y + tmp.z;

			return res;
		}

		Vector3D DivideByScalar(double scale)
		{
			Vector3D res;

			res.x = x / scale;
			res.y = y / scale;
			res.z = z / scale;

			return res;
		}

		Vector3D MultiplyByScalar(double scale)
		{
			Vector3D res;

			res.x = x * scale;
			res.y = y * scale;
			res.z = z * scale;

			return res;
		}

		bool IsEqual(Vector3D a2)
		{
			if (x == a2.x && y == a2.y && z == a2.z)
			{
				return true;
			}

			return false;
		}
	};

	struct Point3D {
		double x;
		double y;
		double z;

		Point3D Add(Point3D vec2)
		{
			Point3D res;

			res.x = x + vec2.x;
			res.y = y + vec2.y;
			res.z = z + vec2.z;

			return res;
		}

		Point3D Subtract(Point3D vec2)
		{
			Point3D res;

			res.x = x - vec2.x;
			res.y = y - vec2.y;
			res.z = z - vec2.z;

			return res;
		}

		//Point3D SubtractVector(Vector3D vec)
		//{
		//	Point3D res;

		//	res.x = x - vec.x;
		//	res.y = y - vec.y;
		//	res.z = z - vec.z;

		//	return res;
		//}

		Point3D DivideByScalar(double scale)
		{
			Point3D res;

			res.x = x / scale;
			res.y = y / scale;
			res.z = z / scale;

			return res;
		}

		Point3D MultiplyByScalar(double scale)
		{
			Point3D res;

			res.x = x * scale;
			res.y = y * scale;
			res.z = z * scale;

			return res;
		}

		bool IsEqual(Point3D a2)
		{
			if (x == a2.x && y == a2.y && z == a2.z)
			{
				return true;
			}

			return false;
		}
	};

	struct Angle3D { double zAngle; double xyAngle; };
}