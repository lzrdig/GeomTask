using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CylinderWrapperCSharp
{
    public class NativeMethods
    {
        //Driver DLLs
        [DllImport("Cylinder.dll")]
        public static extern double GetDistFromPtToCylinder(double radius,
            double bottomX, double bottomY, double bottomZ,
            double topX, double topY, double topZ,
            double ptX, double ptY, double ptZ
        );
    }
}
