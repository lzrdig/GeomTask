// GeomTask.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CommonDeclares.h"
#include "Cylinder.h"

using namespace GeomTask;


extern "C" __declspec(dllexport) double __cdecl GetDistFromPtToCylinder(double radius,
	double bottomX, double bottomY, double bottomZ,
	double topX, double topY, double topZ,
	double ptX, double ptY, double ptZ
	)
{
	double dist = 0.0;

	Point3D botPt{ bottomX, bottomY, bottomZ };
	Point3D topPt{ topX, topY, topZ };
	Point3D testPt{ ptX, ptY, ptZ };

	Cylinder cyl{radius,botPt, topPt};

	cyl.DistanceFromPtToCyl(testPt);

	return dist;
}


