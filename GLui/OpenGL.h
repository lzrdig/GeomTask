#if !defined(__OPENGL_H__)
#define		 __OPENGL_H__

#include "gl\gl.h"
#include "gl\glu.h"
#include "ClassArr.h"
#include "Str.h"

namespace OpenGLui
{
#define Draw3DLine(x1,y1,z1,x2,y2,z2) \
		glBegin(GL_LINES); \
		glVertex3f((x1),(y1),(z1)); \
		glVertex3f((x2),(y2),(z2)); \
		glEnd();

	struct CXYZW { float* x; float* y; float* z; float* w; };
	struct CFRGB { float r; float g; float b; };
	struct Point3D {
		float x; float y; float z;

		Point3D operator=(const Point3D& newPt) {
			Point3D ptOrig{ 0,0,0 };

			this->x = newPt.x;
			this->y = newPt.y;
			this->z = newPt.z;

			return ptOrig;
		}
	};
	enum   CDataGroup { G3D, GTRUE3D, G4D, G4DNOPROP, G4DHASPROP };
	enum   CMapType { FLAT, GRID, SURFACE, BLOCK, NOPROPERTY4D, PROPERTY4D };
	enum   CRotateType { RX, RY, RZ, RXY, RXZ, RYZ, RXYZ, NONE };
	enum   CLinkType { NoLink, XYLink, XZLink, YZLink, XYZLink };
	enum   CMoveType { MOVE, RANDROTAT, CENTERROTAT };

	struct CMarker
	{
		float	x;
		float	y;
		float	Hight;
		int		Flag;
		CStr	Name;
	};

	typedef CClassArray<CMarker, CMarker&>	CMarkArray;

	struct CDataSet
	{
		CStr		m_MapName;

		CLinkType	m_Link;
		CMapType	m_MapType;
		CRotateType	m_Rotate;
		CMoveType	m_Move;

		CFRGB m_BackCr;
		CFRGB m_MinCr;
		CFRGB m_MaxCr;
		CFRGB m_BorderCr;
		bool  m_bAutoCr;
		int	  m_nCrLevel;
		int	  m_nUserCrNum;
		float m_fCrThreshold;
		CClassArray<COLORREF, COLORREF&> m_UserCr;

		int   m_bAxes;
		int   m_bLegend;
		int   m_bBorder;
		int   m_bSide;
		int   m_bBase;

		int   nDataGroup;
		int	  nX;
		int	  nY;
		int	  nZ;
		float m_fXmin;
		float m_fXmax;
		float m_fYmin;
		float m_fYmax;
		float m_fZmin;
		float m_fZmax;
		float m_fWmin;
		float m_fWmax;

		float m_fDx;
		float m_fDy;
		int	  m_xLgdOs;  // legend offset
		int   m_yLgdOs;

		// rotation, transformation, scaling
		float m_xRotat;
		float m_yRotat;
		float m_zRotat;
		float m_xTrans;
		float m_yTrans;
		float m_zTrans;
		float m_xScale;
		float m_yScale;
		float m_zScale;

		CMarkArray m_Marker;
		CFRGB m_MarkerCr;
		int   m_bMark;
		int   m_bLable;
		int   m_bMarkLine;
		int   m_nMarkIndex;

	};


	class COpenGL
	{
	public:
		CStr		m_Version;
		CDataSet*	m_pDS;
		CDataGroup	m_DataGroup;
		bool		m_bMirror;

		COpenGL();
		~COpenGL() { ; }

		// OpenGL initialization
		bool InitOpenGL(HWND hWnd);
		void DestroyOpenGL();
		void OpenGLSize(int cx, int cy);
		void OpenGLTimer(CRotateType type);
		void SetOpenGLTimer(int);
		void KillOpenGLTimer(int);
		void MouseMove(UINT nFlags, POINT point);
		void LButtonDown(POINT point);
		//void LButtonUp(POINT point)		{ m_bLButtonDown = false; }
		void LButtonUp() { m_bLButtonDown = false; }
		//unitquaternion RotationFromMove(const vector& vfrom,const vector& vto);

		// raster font support
		void RasterFont();
		void PrintString(const char *str);

		void OpenGLRendering();
		void DrawBorder();
		void DrawAxis();
		void DrawLegend();
		void DrawCylinder();
		void DrawGeomLine();
		void DrawSphere();
		void SetCylinderParams(Point3D dBottomCenter, Point3D dTopCenter, double dBottomRadius, int nSlices, int nStacks);
		void SetTestPointParams(Point3D dSphereCenter, double dSphereRadius);
		void SetEndPointParams(Point3D dSphereCenter, double dSphereRadius);

		virtual void OpenGLDrawMap() = 0;
		virtual void GDIDrawMap() = 0;
		virtual void OpenGLDrawBanner();
		virtual void GDIDrawBanner();
		virtual void ColorLevel(float level);
		virtual void DrawBox() {}
		virtual void Legend(RECT& rt) { rt.bottom = 0; }
		virtual void OpenMaps(unsigned int) {}
		virtual void SaveMaps(unsigned int) {}



		bool LoadMarkerData(const char* FileName);

		HWND	m_hWnd;
		HDC		m_hDC;
		HGLRC	m_hGLContext;
		GLuint  m_nFontOffset;
		int     m_nTimerSpeed;

		// Mouse 
		bool	m_bLButtonDown;
		bool	m_bRButtonDown;
		bool	m_bDrawNothing;
		POINT	m_LDownPos;
		POINT	m_RDownPos;
		HCURSOR m_CursorRotation;
		float	m_fC;			// For coordinate transform

		// Position, rotation ,scaling
		float	m_fDY;
		float	m_fAngleX;
		float	m_fAngleY;
		float	m_fAngleZ;

		float	m_fDelta;
		int		m_nD;
		bool	m_bDraw;

	private:
		bool	SetWindowPixelFormat();
		bool	CreateViewGLContext();

		int     m_nWidth;
		int     m_nHeight;
		float   m_fDV;

		// Cylinder specs
		Point3D m_dBottomCenter, m_dTopCenter;
		double m_dBottomRadius, m_dTopRadius;
		int m_nSlices, m_nStacks;

		// TestPoint specs (drawn as a sphere)
		Point3D m_ptTestPtCtr;
		double m_dSphRadius;
		Point3D m_ptFoundPtCtr;
	};

}

#endif
