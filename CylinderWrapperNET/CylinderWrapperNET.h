// CylinderWrapperNET.h

#pragma once

using namespace System;
using namespace GeomTask;

namespace CylinderWrapperNET 
{
	public ref class CylinderWrapper
	{
	private:
		Cylinder *_cylObj;
	public:
		CylinderWrapper() : _cylObj(new Cylinder()) {};

		CylinderWrapper(double radius, double height)
		{
			_cylObj = new Cylinder(radius, height);
		}

		CylinderWrapper(double radius, 
			double bottomX, double bottomY, double bottomZ,
			double topX, double topY, double topZ
		);

		~CylinderWrapper()
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

			void set(double value)
			{
				_cylObj->SetRadius(value);
			}
		}

		property double height
		{
			double get()
			{
				return _cylObj->GetHeight();
			}

			void set(double value)
			{
				_cylObj->SetHeight(value);
			}
		}

		property double bottomX
		{
			double get()
			{
				return _cylObj->GetBottomPt().x;
			}
		}


		double GetDistanceFromPtToCyl(double ptX, double ptY, double ptZ);
	};

}
