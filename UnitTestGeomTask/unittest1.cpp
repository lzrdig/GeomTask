#include "stdafx.h"
#include "CppUnitTest.h"
#include "../CylinderLIB/Cylinder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GeomTask;

namespace UnitTestGeomTask
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestCylinder1)
		{// test cylinder creators (along the way the accessors)
			double radius = 0.1;
			double height = 0.5;
			Point3D bottomPt{ 0.0, 1.0, 0.0 };
			Point3D topPt{ 0.0, 1.5, 0.0 };

			Cylinder* cylObj = new Cylinder(radius, height);

			Assert::AreEqual(radius, cylObj->GetRadius(), 0.0);
			Assert::AreEqual(height, cylObj->GetHeight(), 0.0);
			Assert::AreEqual(0.0, cylObj->GetBottomPt().x, 0.0);
			Assert::AreEqual(0.0, cylObj->GetBottomPt().y, 0.0);
			Assert::AreEqual(0.0, cylObj->GetBottomPt().z, 0.0);
			Assert::AreEqual(0.0, cylObj->GetTopPt().x, 0.0);
			Assert::AreEqual(0.0, cylObj->GetTopPt().y, 0.0);
			Assert::AreEqual(height, cylObj->GetTopPt().z, 0.0);

			cylObj = new Cylinder(0.1, bottomPt, topPt);

			Assert::AreEqual(radius, cylObj->GetRadius(), 0.0);
			Assert::AreEqual(height, cylObj->GetHeight(), 0.0);
			Assert::AreEqual(bottomPt.x, cylObj->GetBottomPt().x, 0.0);
			Assert::AreEqual(bottomPt.y, cylObj->GetBottomPt().y, 0.0);
			Assert::AreEqual(bottomPt.z, cylObj->GetBottomPt().z, 0.0);
			Assert::AreEqual(topPt.x, cylObj->GetTopPt().x, 0.0);
			Assert::AreEqual(topPt.y, cylObj->GetTopPt().y, 0.0);
			Assert::AreEqual(topPt.z, cylObj->GetTopPt().z, 0.0);
		}

		TEST_METHOD(TestCylinder2)
		{// test DistanceFormPtToCyl
			Point3D bottomPt { 0.0,0.0,0.5 };
			Point3D topPt    { 0.0,0.0,1.0 };
			double radius = 0.1;

			Cylinder* pCylObj = new Cylinder(radius, bottomPt, topPt);
			Point3D tstPt{ 0.0,0.0,1.5 };


			// test point above the top cap
			Assert::AreEqual(radius, pCylObj->GetRadius(), 0.0);
			Assert::AreEqual(0.5, pCylObj->DistanceFromPtToCyl(tstPt), 0.0);
		}

		TEST_METHOD(TestCylinder2_1)
		{// test DistanceFormPtToCyl
			Point3D bottomPt{ 0.0,0.0,0.5 };
			Point3D topPt{ 0.0,0.0,1.0 };
			double radius = 0.1;

			Cylinder* pCylObj = new Cylinder(radius, bottomPt, topPt);
			Point3D tstPt{ 0.0,0.0,1.5 };

			// test point in between caps and outside the cylinder radius
			tstPt.y = 1.0;
			tstPt.z = 0.9;

			Assert::AreEqual(radius, pCylObj->GetRadius(), 0.0);
			Assert::AreEqual(0.9, pCylObj->DistanceFromPtToCyl(tstPt), 0.1);

			tstPt.y = 1.0;
			tstPt.z = 0.5;

			Assert::AreEqual(0.9, pCylObj->DistanceFromPtToCyl(tstPt), 0.01);
		}

		TEST_METHOD(TestCylinder2_2)
		{// test DistanceFormPtToCyl
			Point3D bottomPt{ 0.0,0.0,0.5 };
			Point3D topPt{ 0.0,0.0,1.0 };
			double radius = 0.1;

			Cylinder* pCylObj = new Cylinder(radius, bottomPt, topPt);
			Point3D tstPt{ 0.0,0.0,1.5 };


			// test point below the bottom cap
			tstPt.y = 1.0;
			tstPt.z = 0.2;

			Assert::AreEqual(0.9, pCylObj->DistanceFromPtToCyl(tstPt), 0.0000001);
		}

		TEST_METHOD(TestCylinder3)
		{
			Point3D bottomPt{ 0,0,0 };
			Point3D topPt{ 0,0,1 };

			Cylinder cylObj(0.1, bottomPt, topPt);
			Point3D tstPt{ 0,0,1 };


			Assert::AreEqual(1.0, cylObj.GetHeight(), 0.0);

			Assert::AreEqual(0.0, cylObj.DistanceFromPtToCyl(tstPt), 0.0);
		}

		TEST_METHOD(TestCylinder4)
		{
			Point3D bottomPt{ 0,0,0 };
			Point3D topPt{ 0,0,1 };

			Cylinder cylObj(0.1, bottomPt, topPt);
			Point3D tstPt{ 0,1,0 };


			Assert::AreEqual(1.0, cylObj.GetHeight(), 0.0);

			Assert::AreEqual(0.9, cylObj.DistanceFromPtToCyl(tstPt), 0.0);
		}

		TEST_METHOD(TestCylinder5)
		{// test cylinder creators
			double radius = 0.1;
			double height = 0.5;
			Point3D bottom{ 0.0, 1.0, 0.0 };
			Point3D top{ 0.0, 2.0, 0.0 };

			Cylinder cylObj(radius, height);
			Point3D tstPt{ 0,0,1 };

			Assert::AreEqual(radius, cylObj.GetRadius(), 0.0);
			Assert::AreEqual(height, cylObj.GetHeight(), 0.0);

			Assert::AreEqual(0.5, cylObj.DistanceFromPtToCyl(tstPt), 0.00001);
		}
	};
}