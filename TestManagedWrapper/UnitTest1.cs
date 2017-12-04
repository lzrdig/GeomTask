using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using CylinderWrapperCSharp;

namespace TestManagedWrapper
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            double distance = 0.0;

            double radius = 10.5;
            double bottomX = 0.0; double bottomY = 0.0; double bottomZ = 0.0;
            double topX = 0.0; double topY = 0.0; double topZ = 20.0;

            double testptx = 0.0; double testpty = 0.0; double testptz = 30.0;

            using (NativeMethods cylDLL = new NativeMethods())
            {
                distance = cylDLL.GetDistanceFromPt2Cyl(radius,
                            bottomX, bottomY, bottomZ,
                            topX, topY, topZ,
                            testptx, testpty, testptz
                            );
            }

            //distance = GetDistFromPtToCylinder(radius,
            //                bottomX, bottomY, bottomZ,
            //                topX, topY, topZ,
            //                testptx, testpty, testptz
            //                );

            Assert.AreEqual(distance,Math.Abs(testptz - topZ));
        }
    }
}
