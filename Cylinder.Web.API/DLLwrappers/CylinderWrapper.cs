using System;
using System.Runtime.InteropServices;




//this is in C#
//double GetDistFromPtToCylinder(double radius,
//    double bottomX, double bottomY, double bottomZ,
//    double topX, double topY, double topZ,
//    double ptX, double ptY, double ptZ
//    )
//public static extern double GetDistFromPtToCylinder(double radius,
//    double bottomX, double bottomY, double bottomZ,
//    double topX, double topY, double topZ,
//    double ptX, double ptY, double ptZ
//    );



namespace Cylinder.API.DLLwrappers
{
    public class CylinderWrapper
    {
        /*
        class PINVOKELIB_API CTestClass 
        {
            public:
                CTestClass( void );
                int DoSomething( int i );
            private:
                int m_member;
        }; 
        */
        [DllImport("Cylinder.dll",
        EntryPoint = "?DoSomething@CTestClass@@QAEHH@Z",
        CallingConvention = CallingConvention.ThisCall)]
        public static extern int TestThisCalling(IntPtr ths, int i);
        // CTestClass* CreateTestClass();
        [DllImport("..\\LIB\\PinvokeLib.dll")]
        public static extern IntPtr CreateTestClass();
        // void DeleteTestClass( CTestClass* instance )
        [DllImport("..\\LIB\\PinvokeLib.dll")]
        public static extern void DeleteTestClass(IntPtr instance);
    }
}
