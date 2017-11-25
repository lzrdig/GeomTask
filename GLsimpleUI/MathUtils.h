#pragma once

namespace SimpleGL
{
#define Draw3DLine(x1,y1,z1,x2,y2,z2) \
		glBegin(GL_LINES); \
		glVertex3f((x1),(y1),(z1)); \
		glVertex3f((x2),(y2),(z2)); \
		glEnd();

	struct Vector3D {
		float x;
		float y;
		float z;

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

		Vector3D Add(Vector3D pt2)
		{
			Vector3D res;

			res.x = x + pt2.x;
			res.y = y + pt2.y;
			res.z = z + pt2.z;

			return res;
		}

		Vector3D Subtract(Vector3D pt2)
		{
			Vector3D res;

			res.x = x - pt2.x;
			res.y = y - pt2.y;
			res.z = z - pt2.z;

			return res;
		}

		double DotProduct(Vector3D pt2)
		{
			Vector3D tmp;
			double res;

			tmp.x = x * pt2.x;
			tmp.y = y * pt2.y;
			tmp.z = z * pt2.z;

			res = tmp.x + tmp.y + tmp.z;

			return res;
		}

		Vector3D DivideByScalar(double scale)
		{
			Vector3D res;

			res.x = x / (float)scale;
			res.y = y / (float)scale;
			res.z = z / (float)scale;

			return res;
		}

		Vector3D MultiplyByScalar(double scale)
		{
			Vector3D res;

			res.x = x * (float)scale;
			res.y = y * (float)scale;
			res.z = z * (float)scale;

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
		float x;
		float y;
		float z;

		void operator=(const Point3D& pt2) {
			x = pt2.x;
			y = pt2.y;
			z = pt2.z;
		}

		Point3D Add(Point3D pt2);

		Point3D Subtract(Point3D pt2);

		Point3D SubtractVector(Vector3D vec);

		Point3D DivideByScalar(double scale);

		Point3D MultiplyByScalar(double scale);

		Vector3D ConvertToVector3D();
	};
	struct Angle3D { float zAngle; float xyAngle; };
}