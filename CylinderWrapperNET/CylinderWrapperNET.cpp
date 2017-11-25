// This is the main DLL file.

#include "stdafx.h"

#include "CylinderWrapperNET.h"

namespace CylinderWrapperNET
{
	double CylinderWrapper::GetDistanceFromPtToCyl(double ptX, double ptY, double ptZ)
	{
		double dist = 0.0;
		Point3D dPoint{ ptX, ptY, ptZ };

		_cylObj->DistanceFromPtToCyl(dPoint);

		return dist;
	}

	CylinderWrapper::CylinderWrapper(double radius,
		double bottomX, double bottomY, double bottomZ,
		double topX, double topY, double topZ)
	{
		Point3D pt1{ bottomX, bottomY, bottomZ };
		Point3D pt2{ topX, topY, topZ };

		_cylObj = new Cylinder(radius, pt1, pt2);
	}
}