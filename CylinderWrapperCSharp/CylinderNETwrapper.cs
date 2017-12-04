using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CylinderWrapperCSharp
{
    public class NativeMethods:IDisposable
    {
        [DllImport("Cylinder.dll", EntryPoint = "GetDistFromPtToCylinder", CallingConvention = CallingConvention.Cdecl)]
        protected static extern double _GetDistFromPtToCylinder(double radius,
            double bottomX, double bottomY, double bottomZ,
            double topX, double topY, double topZ,
            double ptX, double ptY, double ptZ
        );

        public NativeMethods()
        {
            //_workerId = _CreateWorker();
        }

        public double GetDistanceFromPt2Cyl(double radius,
            double bottomX, double bottomY, double bottomZ,
            double topX, double topY, double topZ,
            double ptX, double ptY, double ptZ
         )
        {
            double dist = _GetDistFromPtToCylinder(radius, 
                bottomX, bottomY, bottomZ, 
                topX, topY, topZ,
                ptX, ptY, ptZ);

            return dist;
        }

        public void Dispose()
        {
            //_DeleteWorker(_workerId);
        }

        ~NativeMethods() // Finalize
        {
            Dispose();
        }
    }
}
