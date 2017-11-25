#pragma once
#include "Cylinder.h"
#include "CommonDeclares.h"

using namespace GeomTask;


ref class ManagedCylWrapper
{
private:
	Cylinder *_cylObj;
public:
	ManagedCylWrapper(double radius, double height)
	{
		_cylObj = new Cylinder(radius, height);
	}
	~ManagedCylWrapper()
	{
		delete _cylObj;
		_cylObj = 0;
	}

	property double radius
	{
		 double get()
		{
			return _cylObj->GetRadius();
		}
	}

	property double height
	{
		double get()
		{
			return _cylObj->GetHeight();
		}
	}
};

